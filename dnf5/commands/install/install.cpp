/*
Copyright Contributors to the libdnf project.

This file is part of libdnf: https://github.com/rpm-software-management/libdnf/

Libdnf is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

Libdnf is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with libdnf.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "install.hpp"

#include <dnf5/shared_options.hpp>
#include <libdnf/conf/const.hpp>

namespace dnf5 {

using namespace libdnf::cli;

void InstallCommand::set_parent_command() {
    auto * arg_parser_parent_cmd = get_session().get_argument_parser().get_root_command();
    auto * arg_parser_this_cmd = get_argument_parser_command();
    arg_parser_parent_cmd->register_command(arg_parser_this_cmd);
    arg_parser_parent_cmd->get_group("software_management_commands").register_argument(arg_parser_this_cmd);
}

void InstallCommand::set_argument_parser() {
    auto & ctx = get_context();
    auto & parser = ctx.get_argument_parser();

    auto & cmd = *get_argument_parser_command();
    cmd.set_description("Install software");

    auto keys = parser.add_new_positional_arg("specs", ArgumentParser::PositionalArg::AT_LEAST_ONE, nullptr, nullptr);
    keys->set_description("List of package specs to install");
    keys->set_parse_hook_func(
        [this]([[maybe_unused]] ArgumentParser::PositionalArg * arg, int argc, const char * const argv[]) {
            for (int i = 0; i < argc; ++i) {
                pkg_specs.emplace_back(argv[i]);
            }
            return true;
        });
    keys->set_complete_hook_func([&ctx](const char * arg) { return match_specs(ctx, arg, false, true, true, false); });
    cmd.register_positional_arg(keys);

    allow_erasing = std::make_unique<AllowErasingOption>(*this);

    advisory_name = std::make_unique<AdvisoryOption>(*this);
    advisory_security = std::make_unique<SecurityOption>(*this);
    advisory_bugfix = std::make_unique<BugfixOption>(*this);
    advisory_enhancement = std::make_unique<EnhancementOption>(*this);
    advisory_newpackage = std::make_unique<NewpackageOption>(*this);
    advisory_severity = std::make_unique<AdvisorySeverityOption>(*this);
    advisory_bz = std::make_unique<BzOption>(*this);
    advisory_cve = std::make_unique<CveOption>(*this);

    auto skip_unavailable = std::make_unique<SkipUnavailableOption>(*this);
    auto skip_broken = std::make_unique<SkipBrokenOption>(*this);
}

void InstallCommand::configure() {
    auto & context = get_context();
    context.update_repo_metadata_from_specs(pkg_specs);
    context.set_load_system_repo(true);
    bool updateinfo_needed = advisory_name->get_value().empty() || advisory_security->get_value() ||
                             advisory_bugfix->get_value() || advisory_enhancement->get_value() ||
                             advisory_newpackage->get_value() || advisory_severity->get_value().empty() ||
                             advisory_bz->get_value().empty() || advisory_cve->get_value().empty();
    if (updateinfo_needed) {
        context.base.get_config().get_optional_metadata_types_option().add_item(libdnf::METADATA_TYPE_UPDATEINFO);
    }

    context.set_load_available_repos(Context::LoadAvailableRepos::ENABLED);
}

void InstallCommand::run() {
    auto & ctx = get_context();
    auto goal = get_context().get_goal();
    goal->set_allow_erasing(allow_erasing->get_value());
    auto settings = libdnf::GoalJobSettings();
    auto advisories = advisory_query_from_cli_input(
        ctx.base,
        advisory_name->get_value(),
        advisory_security->get_value(),
        advisory_bugfix->get_value(),
        advisory_enhancement->get_value(),
        advisory_newpackage->get_value(),
        advisory_severity->get_value(),
        advisory_bz->get_value(),
        advisory_cve->get_value());
    if (advisories.has_value()) {
        settings.set_advisory_filter(std::move(advisories.value()));
    }
    for (const auto & spec : pkg_specs) {
        goal->add_install(spec, settings);
    }
}

}  // namespace dnf5

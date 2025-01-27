/*
OBS Background Removal Filter Plugin
Copyright (C) 2021 Roy Shilkrot roy.shil@gmail.com

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program. If not, see <https://www.gnu.org/licenses/>
*/

#include <obs-module.h>

#include "plugin-support.h"

#include "update-checker/github-utils.h"
#include "update-checker/update-checker.h"

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE(PLUGIN_NAME, "en-US")

MODULE_EXPORT const char *obs_module_description(void)
{
	return obs_module_text("PortraitBackgroundFilterPlugin");
}

extern struct obs_source_info background_removal_filter_info;
extern struct obs_source_info enhance_filter_info;

bool obs_module_load(void)
{
	obs_register_source(&background_removal_filter_info);
	obs_register_source(&enhance_filter_info);
	obs_log(LOG_INFO, "plugin loaded successfully (version %s)",
		PLUGIN_VERSION);

	const struct github_utils_release_information latestRelease =
		github_utils_get_release_information();
	if (latestRelease.responseCode == OBS_BGREMOVAL_GITHUB_UTILS_SUCCESS) {
		obs_log(LOG_INFO, "Latest release is %s",
			latestRelease.version);
		check_update(latestRelease);
	} else {
		obs_log(LOG_INFO, "failed to get latest release information");
	}
	github_utils_release_information_free(latestRelease);

	return true;
}

void obs_module_unload()
{
	obs_log(LOG_INFO, "plugin unloaded");
}

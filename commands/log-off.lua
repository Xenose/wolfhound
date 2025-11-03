HELP = HELP or false

if (HELP) then
	COMMAND_INFO = {
		create = "2025-11-03",
		description = "",
	}

	return COMMAND_INFO
else
	if (nil ~= args) then
		for index, value in ipairs(args) do
			if "debug" == value then
				WH.config.flags.log_debug			= false
			elseif "info" == value then
				WH.config.flags.log_info			= false
			elseif "notice" == value then
				WH.config.flags.log_notice			= false
			elseif "warning" == value then
				WH.config.flags.log_warning		= false
			elseif "error" == value then
				WH.config.flags.log_error			= false
			elseif "critical" == value then
				WH.config.flags.log_critical		= false
			elseif "alert" == value then
				WH.config.flags.log_alert			= false
			elseif "emergency" == value then
				WH.config.flags.log_emergency		= false
			end
		end
	end
end

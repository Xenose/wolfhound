HELP = HELP or false

if (HELP) then
	COMMAND_INFO = {
		create = "2025-11-03",
		description = "test",
	}

	return COMMAND_INFO
else
	if (nil ~= args) then
		for index, value in ipairs(args) do
			if "debug" == value then
				WH.config.flags.log_debug			= true
			elseif "info" == value then
				WH.config.flags.log_info			= true
			elseif "notice" == value then
				WH.config.flags.log_notice			= true
			elseif "warning" == value then
				WH.config.flags.log_warning		= true
			elseif "error" == value then
				WH.config.flags.log_error			= true
			elseif "critical" == value then
				WH.config.flags.log_critical		= true
			elseif "alert" == value then
				WH.config.flags.log_alert			= true
			elseif "emergency" == value then
				WH.config.flags.log_emergency		= true
			end
		end
	end
end

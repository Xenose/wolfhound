HELP = HELP or false

if (HELP) then
	COMMAND_INFO = {
		create = "2025-11-12",
		description = "",
	}

	return COMMAND_INFO
else
	if (nil ~= args) then
		for index, value in ipairs(args) do
			if "on" == value then
				WH.config.flags.memory.tracking = true
			elseif "off" == value then
				WH.config.flags.memory.tracking = false
			end
		end
	end
end

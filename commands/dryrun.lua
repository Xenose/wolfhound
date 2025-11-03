HELP = HELP or false


if (HELP) then
	COMMAND_INFO = {
		create = "2025-05-20",
		description = "Runs the program once with one loop execution.",
	}

	return COMMAND_INFO
else
	if (nil ~= args) then
		print("--> " .. table.concat(args, ", "))
	end

	WH.config.flags.dryrun = true
end

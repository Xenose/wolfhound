

local failed_count=0
local cases = {
	{0, 0, 0},
	{10, 1, 10},
	{100, 10, 10},
	{1000, 100, 10}
}

for i = 1, #cases do
	local result = WH.maths.int.pow(cases[i][2], cases[i][3])

	if cases[i][1] ~= result then
		failed_count = failed_count + 1
		print("Failed test case pow(" .. tostring(cases[i][2]) .. "," .. tostring(cases[i][3]) .. ") [ " .. tostring(i) .. " ] value out is [ " .. tostring(result) .. " ]")
	else
		print("Passed test case pow(" .. tostring(cases[i][2]) .. "," .. tostring(cases[i][3]) .. ") [ " .. tostring(i) .. " ] value out is [ " .. tostring(result) .. " ]")
	end
end

return failed_count

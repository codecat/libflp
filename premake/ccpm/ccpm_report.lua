function ccpm_report()
	term.pushColor(term.yellow)
	print('===== CCPM build =====')
	print('%')

	print('%  Host: ' .. os.host())
	print('%  Target: ' .. os.target())
	print('%')

	print('%  Output: bin/')
	print('%  Build: projects/' .. _ACTION .. '/')
	print('%')

	if ccpm_option_on('x86') then
		print('%  Option: x86')
	end

	if ccpm_option_on('x64') then
		print('%  Option: x64')
	end

	if os.target() == 'windows' and os.host() ~= 'windows' then
		print('%  Option: mingw')
	end

	print('%')

	for _, pkg in ipairs(CCPM_GLOBAL_PACKAGES) do
		print('%  Package "' .. pkg.id .. '"')
	end

	print('%')

	for _, ws in ipairs(CCPM_GLOBAL_WORKSPACES) do
		print('%  Workspace "' .. ws.name .. '"')
		for _, proj in ipairs(ws.projects) do
			print('%  - Project "' .. proj.name .. '" (' .. proj.current.kind .. ')')
		end
	end

	print('%')
	term.popColor()
end

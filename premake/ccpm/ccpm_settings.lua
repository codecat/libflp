local allowed_on_off = {
	{ '', 'On.' },
	{ 'on', 'On.' },
	{ 'off', 'Off.' },
}

newoption {
	trigger = 'x86',
	description = 'Enables x86 builds.',
	default = 'off',
	allowed = allowed_on_off
}

newoption {
	trigger = 'x64',
	description = 'Enables x64 builds.',
	default = 'on',
	allowed = allowed_on_off
}

function ccpm_option_on(name)
	local o = _OPTIONS[name]

	if not o then
		return false
	end

	return o ~= 'off'
end

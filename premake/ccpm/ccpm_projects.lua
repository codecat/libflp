function ccpm_workspace(name)
	table.insert(CCPM_GLOBAL_WORKSPACES, workspace(name))
		targetdir('bin/')
		location(path.join('projects', _ACTION))

		language('C++')
		cppdialect('C++17')

		configurations { 'Debug', 'Release' }

		if ccpm_option_on('x86') then
			platforms { 'x86' }
		end
		if ccpm_option_on('x64') then
			platforms { 'x64' }
		end
end

function ccpm_project(name)
	project(name)
		debugdir('bin/')
		flags { 'MultiProcessorCompile' }

		filter { 'platforms:x86' }
			architecture('x86')
		filter { 'platforms:x64' }
			architecture('x86_64')
		filter {}

		filter { 'configurations:Debug' }
			defines { 'DEBUG' }
			symbols 'On'
		filter { 'configurations:Release' }
			defines { 'RELEASE' }
			optimize 'On'
		filter {}

		filter { 'system:windows' }
			defines { 'PLATFORM_WINDOWS', '_CRT_SECURE_NO_WARNINGS', 'NOMINMAX' }
		filter { 'system:linux' }
			defines { 'PLATFORM_LINUX' }
		filter { 'system:macosx' }
			defines { 'PLATFORM_MACOS' }
		filter {}

		if os.target() == 'windows' and os.host() ~= 'windows' then
			filter { 'platforms:x86' }
				gccprefix('i686-w64-mingw32-')
			filter { 'platforms:x64' }
				gccprefix('x86_64-w64-mingw32-')
			filter {}
		end

		targetsuffix('-%{cfg.platform}-%{cfg.buildcfg}')
end

function ccpm_consoleapp(name)
	ccpm_project(name)
		kind('ConsoleApp')
end

function ccpm_app(name)
	ccpm_project(name)
		kind('WindowedApp')
end

function ccpm_dll(name)
	ccpm_project(name)
		kind('SharedLib')
end

function ccpm_lib(name)
	ccpm_project(name)
		kind('StaticLib')
end

function ccpm_sources(dir)
	files {
		path.join(dir, '**.cpp'),
		path.join(dir, '**.hpp'),
		path.join(dir, '**.c'),
		path.join(dir, '**.h'),
	}

	includedirs { dir }
end

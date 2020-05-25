dofile('premake/ccpm/ccpm.lua')

ccpm_workspace 'libflp'
	ccpm_lib 'flp'
		ccpm_sources 'src/flp'
		ccpm_sources 'include'

	ccpm_consoleapp 'parseflp'
		ccpm_sources 'src/parseflp'
		links 'flp'
		includedirs 'include'

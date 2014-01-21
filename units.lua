require "tundra.syntax.glob"

StaticLibrary {
	Name = "Framework",
	Env = {
		CPPPATH = { 
			"framework",
			".",
			"dependencies/SDL2-2.0.1/include",
		}, 
	},

	Sources = {
		FGlob {
			Dir = "framework",
			Extensions = { ".cpp", ".h", ".inl" },
			Filters = {
				{ Pattern = "win32"; Config = "win32-*-*"; },
				{ Pattern = "macosx"; Config = "macosx-*-*"; },
			},
		},
	},
}

Program {
	Name = "Lab1",
	Env = {
		CPPPATH = { 
			"lab1",
			".",
		}, 
		LIBPATH = {
			"dependencies/SDL2-2.0.1/lib/x86",
		},
		PROGOPTS = {
			{ "/SUBSYSTEM:WINDOWS"; Config = { "win32-*-*" } },
		}
	},
	Sources = {
		FGlob {
			Dir = "lab1",
			Extensions = { ".cpp", ".h", ".inl" },
			Filters = {
				{ Pattern = "win32"; Config = "win32-*-*"; },
				{ Pattern = "macosx"; Config = "macosx-*-*"; },
			},
		},
	},
	Depends = { "Framework" },

	Libs = 
		{ 
			{ 
				"kernel32.lib", 
				"user32.lib", 
				"gdi32.lib", 
				"comdlg32.lib", 
				"advapi32.lib", 
				"SDL2.lib",
				Config = { "win32-*-*", "win64-*-*" } 
			}
		},
}

Default "Lab1"

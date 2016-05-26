TransX64Dbg - Plugin to make x64Dbg Transparent
===============================================

This is a very small plugin written in C, inspired from TransOlly Plugin for OllyDbg.

How to build
------------
Clone whole the project and open sln file with VS2015, then build it

Usage
-----
When plugin is installed and loaded, use commands:
`translv <NUMBER>`: set opacity amount for x64dbg's main Window, the number is percentage, between 0 and 100. For example, `translv 80` set the opacity to 80%.
`translv off` : Disable the opacity
Known bugs
----------
Sometime the opacity value is not loaded at startup, while the plugin is enabled. This may came from pluginsdk issues. I'm figuring it out.

Thanks:

- mr.Exodia and x64dbg Development Team
- My Friends

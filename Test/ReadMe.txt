========================================================================
    CONSOLE APPLICATION : Test Project Overview
========================================================================

AppWizard has created this Test application for you.

This file contains a summary of what you will find in each of the files that
make up your Test application.


Test.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

Test.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

Test.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named Test.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

The application uses the tested project as a static library .lib.
To reflect the changes made in the testable project, make sure to build the
testable project as a static library.

If the linker of the test project complains for unresolved symbols, try the following actions
1. Delete the .exe of the testable project from the Debug folder (if such exists)
2. Change the configuration type of testable project to static library
3. Rebuild the testable project
4. Rebuild the test project.

Repeat until it works, VS2013 is buggy.

/////////////////////////////////////////////////////////////////////////////

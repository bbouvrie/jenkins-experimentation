TEMPLATE = subdirs

SUBDIRS = \
ai_project \
exe_project \
test_example

exe_project.depends = ai_project
test_example.depends = ai_project

OTHER_FILES += .qmake.conf

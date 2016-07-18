
all:
	@echo \#\#teamcity[progressMessage \'Building Cabinet Workspace\']
	codeblocks --multiple-instance --rebuild --target=Debug Cabinet.workspace

	@echo \#\#teamcity[progressMessage \'Running Cabinet Tests\']
	-TestCabinet/bin/Debug/TestCabinet --gtest_output=xml:cabinet-tests.xml
	@echo \#\#teamcity[importData type=\'gtest\' path=\'`pwd`/cabinet-tests.xml\']

	@echo \#\#teamcity[publishArtifacts \'`pwd`/TestCabinet/bin/Debug/TestCabinet\']
	@echo \#\#teamcity[publishArtifacts \'`pwd`/bin/Debug/Cabinet\']


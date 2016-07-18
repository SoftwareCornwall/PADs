
all:
	@echo \#\#teamcity[progressMessage \'Building Cabinet Workspace\']
	codeblocks --multiple-instance --rebuild --target=Debug Cabinet.workspace

	@echo \#\#teamcity[progressMessage \'Running Cabinet Tests\']
	-TestCabinet/bin/Debug/TestCabinet --gtest_output=xml:cabinet-tests.xml
	@echo \#\#teamcity[importData type=\'gtest\' path=\'cabinet-tests.xml\']

	@echo \#\#teamcity[publishArtifacts \'TestCabinet/bin/Debug/TestCabinet\']
	@echo \#\#teamcity[publishArtifacts \'Cabinet/bin/Debug/Cabinet\']


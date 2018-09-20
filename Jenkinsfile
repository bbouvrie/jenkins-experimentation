pipeline {
  agent {
	label 'qt'
  }
  stages {
    stage('build') {
      steps {
		bat 'masterclass-jenkins-compile.bat'
      }
    }
    stage('test') {
      steps {
        bat 'masterclass-jenkins-test'
		xunit (
		  tools: [
		    QtTest(
			  pattern: 'testResults_*.xml',
			  skipNoTestFiles: false,
			  failIfNotNew: true,
			  deleteOutputFiles: true,
			  stopProcessingIfError: true
			)
		  ],
		  thresholds: [],
		  thresholdMode : 1,
		  testTimeMargin : '3000',
		)
      }
    }
  }
  triggers {
    pollSCM('*/5 * * * *')
  }
}
pipeline {
  agent any
  triggers {
	// Poll version control every 5 minutes for changes.
	pollSCM('*/5 * * * *')
  }
  stages {
    stage('build') {
      steps {
        echo 'This is where building the source code happens'
      }
    }
    stage('test') {
      steps {
        echo 'This is where the tests are being executed'
      }
    }
  }
}
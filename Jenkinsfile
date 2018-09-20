pipeline {
  agent any
  triggers {
	pollSCM(0 */5 * ? * *) // Poll version control every 5 minutes for changes.
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
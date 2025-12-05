pipeline {
    agent { label 'agent_1' }

    parameters {
        booleanParam(name: 'CLEAN_BUILD', defaultValue: false, description: 'clean previous "build" folder')
    }

    stages {

        stage('Install OpenSSL') {
            steps {
                script {
                    sh 'apt-get update && apt-get install -y libssl-dev'
                }
            }
        }

        stage('Create a Build Folder') {
            steps {
                script {
                    // Create a build directory
                    sh 'mkdir -p build'
                }
            }
        }

        stage('Run CMake') {
            steps {
                script {
                    // Run CMake to configure the project
                    sh 'cmake -B build'
                }
            }
        }

        stage('Build the Project') {
            steps {
                script {
                    // Compile the project
                    sh 'cmake --build build'
                }
            }
        }
    }
}
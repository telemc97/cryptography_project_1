pipeline {
    agent { label 'agent_1' }

    parameters {
        booleanParam(name: 'CLEAN_BUILD', defaultValue: false, description: 'clean previous "build" folder')
    }

    stages {

        stage('Create a Build Folder') {
            steps {
                script {
                    if (params.CLEAN_BUILD) {
                        sh 'rm -rf build'
                    }
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
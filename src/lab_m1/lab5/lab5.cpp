#include "lab_m1/lab5/lab5.h"


#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;
using namespace glm;


Lab5::Lab5()
{
}


Lab5::~Lab5()
{
}


void Lab5::Init()
{
    renderCameraTarget = false;
    camera = new implemented::Camera();
    camera->Set(glm::vec3(2, 2, 4), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
    HP = maxHP;
    {
        Mesh* bulletMesh = new Mesh("bullet");
        bulletMesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[bulletMesh->GetMeshID()] = bulletMesh;
    }
    {
        Shader* shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab5", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab5", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
    {
        Mesh* mesh = new Mesh("tankBody");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "props"), "tankBody.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("tankTop");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "props"), "tankTop.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("tankWheels");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "props"), "tankWheels.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("tankGun");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "props"), "tankGun.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh1 = new Mesh("building");
        mesh1->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "props"), "building.obj");
        meshes[mesh1->GetMeshID()] = mesh1;
    }

    {
        Mesh* mesh2 = new Mesh("bullet");
        mesh2->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh2->GetMeshID()] = mesh2;
    }
    {
		Mesh* mesh3 = new Mesh("enemyBullet");
		mesh3->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
		meshes[mesh3->GetMeshID()] = mesh3;
	}
    {
        Mesh* mesh4 = new Mesh("cloud");
        mesh4->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "props"), "cloud.obj");
        meshes[mesh4->GetMeshID()] = mesh4;
    }
    {
        Mesh* mesh5 = new Mesh("flower");
        mesh5->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "props"), "flowers.obj");
        meshes[mesh5->GetMeshID()] = mesh5;
    }
    {
        Mesh* mesh6 = new Mesh("grass");
        mesh6->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "props"), "grasspatch.obj");
        meshes[mesh6->GetMeshID()] = mesh6;
    }

    {
		Shader* shader = new Shader("Simple");
		shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab5", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
		shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab5", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
    {
        vector<glm::vec3> vertices {
            glm::vec3(0.5f,  0.5f, 0.0f),
            glm::vec3(0.5f, -0.5f, 0.0f),
            glm::vec3(-0.5f, -0.5f, 0.0f),
            glm::vec3(-0.5f,  0.5f, 0.0f),
        };
        vector<glm::vec3> normals{
            glm::vec3(0, 1, 1),
            glm::vec3(1, 0, 1),
            glm::vec3(1, 0, 0),
            glm::vec3(0, 1, 0)
        };
        vector<glm::vec2> textureCoords{
            glm::vec2(0, 0),
            glm::vec2(0, 1),
            glm::vec2(1, 1),
            glm::vec2(1, 0)
        };
        vector<unsigned int> indices = {
            0, 1, 3,
            1, 2, 3
        };

        Mesh* mesh = new Mesh("square");
        mesh->InitFromData(vertices, normals, textureCoords, indices);
        meshes[mesh->GetMeshID()] = mesh;
    }

    Mesh* bodyMesh = new Mesh("tankBody");
    Mesh* topMesh = new Mesh("tankTop");
    Mesh* gunMesh = new Mesh("tankGun");
    Mesh* wheelsMesh = new Mesh("tankWheels");
    bodyMesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "props"), "tankBody.obj");
    topMesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "props"), "tankTop.obj");
    gunMesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "props"), "tankGun.obj");
    wheelsMesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "props"), "tankGun.obj");


    int B = rand() % 20 + 10; //buildings
    buildings.resize(B);
    for (int i = 0; i < B; i++) {
        glm::vec3 position = glm::vec3(rand() % 100 - 50, 0, rand() % 100 - 50);
        buildings[i].buildingPosition = position;
    }

    int C = 30; // clouds
    clouds.resize(C);
    for (int i = 0; i < C; i++) {
		glm::vec3 position = glm::vec3(rand() % 100 - 50, 7, rand() % 100 - 50);
		clouds[i].cloudPosition = position;
	} 
    
    int G = 20; // grass patches
    grassPatches.resize(G);
    for (int i = 0; i < G; i++) {
        glm::vec3 position = glm::vec3(rand() % 100 - 50, 0, rand() % 100 - 50);
        grassPatches[i].grassPosition = position;
    }

    int F = rand() % 20 + 10; //flowers
    flowers.resize(F);
    for (int i = 0; i < F; i++) {
        glm::vec3 position = glm::vec3(rand() % 100 - 50, 0, rand() % 100 - 50);
        flowers[i].flowerPosition = position;
    }


    int N = rand() % 20 + 10;
    enemyTanks.resize(N);
    for (int i = 0; i < N; i++) {
        int P = rand() % 5 + 5;
        glm::vec3 position = glm::vec3(rand() % 100 - 50, 0.6, rand() % 100 - 50);

        enemyTanks[i].position = position;
        enemyTanks[i].tankBody = meshes["tankBody"];
        enemyTanks[i].tankTop = meshes["tankTop"];
        enemyTanks[i].tankWheels = meshes["tankWheels"];
        enemyTanks[i].tankGun = meshes["tankGun"];
        enemyTanks[i].direction = glm::vec3(rand() % 3 - 1, 0, rand() % 3 - 1);
        enemyTanks[i].movementSpeed = 2.0f;
        enemyTanks[i].changeDirectionTime = 5.0f;
        enemyTanks[i].timeUntilChangeDirection = enemyTanks[i].changeDirectionTime;
        enemyTanks[i].timeSinceLastShot = 0.0f;
        enemyTanks[i].rotationAngle = 0.0f;
        enemyTanks[i].enemyHP = maxEnemyHP;
        enemyTanks[i].currentColor = enemyTanks[i].fullHPColor;
        enemyTanks[i].currentColor2 = enemyTanks[i].fullHPColor2;
        enemyTanks[i].currentColor3 = enemyTanks[i].fullHPColor3;
        enemyTanks[i].hpRatio = static_cast<float>(enemyTanks[i].enemyHP) / maxEnemyHP;
    }
    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
}


void Lab5::FrameStart()
{
    glClearColor(0.7f, 0.8f, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}


void Lab5::Update(float deltaTimeSeconds)
{
    float hpRatio = static_cast<float>(HP) / maxHP;
    glm::vec3 currentColor = glm::mix(zeroHPColor, fullHPColor, hpRatio);
    glm::vec3 currentColor2 = glm::mix(zeroHPColor, fullHPColor2, hpRatio);
    glm::vec3 currentColor3 = glm::mix(zeroHPColor, fullHPColor3, hpRatio);
    glm::vec3 mintGreen = glm::vec3(0.6f, 0.98, 0.6);
    glm::vec3 seaGreen = glm::vec3(0.18f, 0.55f, 0.34f);
    
    {
        glm::mat4 ModelMatrixGround = glm::mat4(1);
        ModelMatrixGround = glm::translate(ModelMatrixGround, glm::vec3(0, 0, 0));
        ModelMatrixGround = glm::scale(ModelMatrixGround, glm::vec3(200, 0.01f, 100));
        ModelMatrixGround = glm::rotate(ModelMatrixGround, RADIANS(90), glm::vec3(1, 0, 0));
        RenderMesh(meshes["square"], shaders["Simple"], ModelMatrixGround, mintGreen);
    }
    {
        glm::mat4 modelMatrixBody = glm::mat4(1);
        modelMatrixBody = glm::translate(modelMatrixBody, tankPosition);
        modelMatrixBody = glm::rotate(modelMatrixBody, tankRotationAngle, glm::vec3(0, 1, 0));
        RenderMesh(meshes["tankBody"], shaders["Simple"], modelMatrixBody, currentColor2);
        RenderMesh(meshes["tankWheels"], shaders["Simple"], modelMatrixBody, currentColor3);

        glm::mat4 modelMatrixTurret = glm::mat4(1);
        modelMatrixTurret = glm::translate(modelMatrixTurret, tankPosition);
        modelMatrixTurret = glm::rotate(modelMatrixTurret, tankRotationAngle, glm::vec3(0, 1, 0));
        modelMatrixTurret = glm::rotate(modelMatrixTurret, turretRotationAngle, glm::vec3(0, 1, 0));
        RenderMesh(meshes["tankTop"], shaders["LabShader"], modelMatrixTurret, currentColor);
        RenderMesh(meshes["tankGun"], shaders["Simple"], modelMatrixTurret, currentColor3);

        RenderHPBar(tankPosition, static_cast<float>(HP) / maxHP, 0);
        


        for (auto& enemyTank : enemyTanks) {
            enemyTank.timeUntilChangeDirection -= deltaTimeSeconds;
            if (enemyTank.timeUntilChangeDirection <= 0) {
                enemyTank.direction = glm::vec3(rand() % 3 - 1, 0, rand() % 3 - 1);
                enemyTank.timeUntilChangeDirection = enemyTank.changeDirectionTime;
            }

            float distanceToPlayer = glm::length(tankPosition - enemyTank.position);
            if (distanceToPlayer <= 20.0f) {
                glm::vec3 directionToMainTank = glm::normalize(tankPosition - enemyTank.position);

                enemyTank.rotationAngle = atan2(directionToMainTank.x, directionToMainTank.z);

                enemyTank.direction = directionToMainTank;

                enemyTank.timeSinceLastShot += deltaTimeSeconds;
                if (enemyTank.timeSinceLastShot >= enemyTank.shootingInterval && enemyTank.isAlive) {
                    ShootEnemyBullet(enemyTank);
                    enemyTank.timeSinceLastShot = 0.0f;
                }
            }
            else {
                enemyTank.position += enemyTank.direction * enemyTank.movementSpeed * deltaTimeSeconds;
            }
            if (CheckCollisionWithEnemyTank(tankPosition, tankRadius) && enemyTank.isAlive) {
                glm::vec3 diff = tankPosition - enemyTank.position;
                glm::vec3 pushbackDirection = glm::normalize(diff);
                tankPosition = tankPosition - pushbackDirection;
            }
        }


        {
            for (const auto& building : buildings) {
                glm::mat4 modelMatrix = glm::mat4(1);
                float rotationAngle = 45;
				modelMatrix = glm::translate(modelMatrix, building.buildingPosition);
                modelMatrix = glm::rotate(modelMatrix, rotationAngle, glm::vec3(0, 1, 0));
				RenderMesh(meshes["building"], shaders["Simple"], modelMatrix, building.color);
                if (CheckCollisionWithBuilding(tankPosition, tankRadius)) {
                    glm::vec3 diff = tankPosition - building.buildingPosition;
                    glm::vec3 pushbackDirection = glm::normalize(diff);
                    tankPosition = tankPosition - pushbackDirection;
                }
            }
        }
        {
            for (const auto& cloud : clouds) {
				glm::mat4 modelMatrixCloud = glm::mat4(1);
                modelMatrixCloud = glm::translate(modelMatrixCloud, cloud.cloudPosition);
                modelMatrixCloud = glm::scale(modelMatrixCloud, glm::vec3(2.0f));
                RenderMesh(meshes["cloud"], shaders["Simple"], modelMatrixCloud, cloud.color);
            }
        }
        {
            for (const auto& flower : flowers) {
                glm::mat4 modelMatrixFlower = glm::mat4(1);
                modelMatrixFlower = glm::translate(modelMatrixFlower, flower.flowerPosition);
                modelMatrixFlower = glm::scale(modelMatrixFlower, glm::vec3(0.1f));
                RenderMesh(meshes["flower"], shaders["Simple"], modelMatrixFlower, flower.color);
            }
        }
        {
            for (const auto& grass : grassPatches) {
                glm::mat4 modelMatrixGrass = glm::mat4(1);
				modelMatrixGrass = glm::translate(modelMatrixGrass, grass.grassPosition);
				modelMatrixGrass = glm::scale(modelMatrixGrass, glm::vec3(0.05f));
				RenderMesh(meshes["grass"], shaders["Simple"], modelMatrixGrass, mintGreen);
            }
        }

        for (const EnemyTank& enemyTank : enemyTanks) {
            if (enemyTank.isAlive) {
                glm::mat4 modelMatrix = glm::mat4(1.0f);
                modelMatrix = glm::translate(modelMatrix, enemyTank.position);
                modelMatrix = glm::rotate(modelMatrix, enemyTank.rotationAngle, glm::vec3(0, 1, 0));
                RenderEnemyTank(const_cast<EnemyTank&>(enemyTank));
                RenderHPBar(enemyTank.position, enemyTank.hpRatio, 1);
            }
        }

        for (auto& bullet : bullets) {
            if (bullet.isActive) {
                for (auto& enemyTank : enemyTanks) {
                    if (CheckCollisionBulletEnemyTank(bullet, enemyTank)) {
                        bullet.isActive = false;
                        enemyTank.enemyHP--;

                        enemyTank.hpRatio = static_cast<float>(enemyTank.enemyHP) / maxEnemyHP;
                        enemyTank.currentColor = glm::mix(zeroHPColor, enemyTank.fullHPColor, enemyTank.hpRatio);
                        enemyTank.currentColor2 = glm::mix(zeroHPColor, enemyTank.fullHPColor2, enemyTank.hpRatio);
                        enemyTank.currentColor3 = glm::mix(zeroHPColor, enemyTank.fullHPColor3, enemyTank.hpRatio);

                        if (enemyTank.enemyHP <= 0) {
                            enemyTank.isAlive = false;
                        }
                    }
                }

                if (bullet.isActive) {
                    bullet.position += bullet.velocity * deltaTimeSeconds;
                    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), bullet.position);
                    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.75f));
                    RenderMesh(meshes["bullet"], shaders["Simple"], modelMatrix, bleu);
                }
            }
        }
        for (auto& enemyBullet : enemyBullets) {
            if (enemyBullet.isActive) {
                enemyBullet.position += enemyBullet.velocity * deltaTimeSeconds;
                glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), enemyBullet.position);
                modelMatrix = glm::scale(modelMatrix, glm::vec3(0.75f));
                RenderMesh(meshes["enemyBullet"], shaders["Simple"], modelMatrix, rodie);
            }
        }
        
        for (auto& enemyBullet : enemyBullets) {
            if (enemyBullet.isActive) {
                if (CheckCollisionWithMainTank(enemyBullet)) {
                    enemyBullet.isActive = false;
                    HP--;
                }
            }
        }
    }

    if (HP == 0) {
        cout << "GAME OVER" << endl;
        exit(0);
    }
}


void Lab5::FrameEnd()
{
    //DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Lab5::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
{
    if (!mesh || !shader || !shader->program)
        return;
    glUseProgram(shader->program);

    GLint objectColorLoc = glGetUniformLocation(shader->program, "object_color");
    glUniform3fv(objectColorLoc, 1, glm::value_ptr(color));

    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}


void Lab5::OnInputUpdate(float deltaTime, int mods)
{
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float cameraSpeed = 4.0f;

        if (window->KeyHold(GLFW_KEY_W)) {
            camera->TranslateForward(deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_A)) {
            camera->TranslateRight(-deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_S)) {
            camera->TranslateForward(-deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_D)) {
            camera->TranslateRight(deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_Q)) {
            camera->TranslateUpward(-deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_E)) {
            camera->TranslateUpward(deltaTime * cameraSpeed);
        }
    }

    if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float tankSpeed = 5;
        tankPosition.y = groundLevel;
        float tankRotationSpeed = 1.0f;
        float cameraSpeed = 5;
        glm::vec3 camPos;
        camPos = tankPosition + glm::vec3(0, 1, 4);

        if (window->KeyHold(GLFW_KEY_A)) {
            tankRotationAngle += tankRotationSpeed * deltaTime;
            camera->RotateThirdPerson_OY(deltaTime * tankRotationSpeed);
            camera->TranslateRight(deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_D)) {
            tankRotationAngle -= tankRotationSpeed * deltaTime;
            camera->RotateThirdPerson_OY(-deltaTime * tankRotationSpeed);
            camera->TranslateRight(-deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_W)) {
            if (window->KeyHold(GLFW_KEY_SPACE)) {
                tankSpeed = 20;
            }
            if (!CheckCollisionWithBuilding(tankPosition, tankRadius) && !CheckCollisionWithEnemyTank(tankPosition, tankRadius)) {
                camera->TranslateForward(deltaTime * tankSpeed);
			}
            glm::vec3 leftDirection = glm::normalize(glm::vec3(cos(tankRotationAngle), 0, -sin(tankRotationAngle)));
            tankPosition += leftDirection * deltaTime * tankSpeed;
        }

        if (window->KeyHold(GLFW_KEY_S)) {
            glm::vec3 rightDirection = glm::normalize(glm::vec3(-cos(tankRotationAngle), 0, sin(tankRotationAngle)));
            tankPosition += rightDirection * deltaTime * tankSpeed;
            camera->TranslateForward(-deltaTime * tankSpeed);
        }
    }
}


void Lab5::OnKeyPress(int key, int mods)
{
}

bool Lab5::CheckCollisionWithMainTank(const enemyBullet& enemyBullet) {
    float tankRadius = 2.0f; 
    float bulletRadius = 0.2f; 

    float distance = glm::distance(enemyBullet.position, tankPosition);

    return distance < (tankRadius + bulletRadius);
}

bool Lab5::CheckCollisionBulletEnemyTank(const Bullet& bullet, const EnemyTank& enemyTank) {
    if (enemyTank.isAlive) {
		float enemyTankRadius = 1.0f;  
		float bulletRadius = 0.2f;   

		float distance = glm::distance(bullet.position, enemyTank.position);

		return distance < (enemyTankRadius + bulletRadius);
	}
}

void Lab5::RotateEnemyTankToFaceMainTank(EnemyTank& enemyTank) {
    glm::vec3 directionToMainTank = glm::normalize(tankPosition - enemyTank.position);

    float rotationAngle = -atan2(directionToMainTank.z, directionToMainTank.x);

    enemyTank.rotationAngle = rotationAngle;
}

float Lab5::CalculateRotationAngleToFaceMainTank(const EnemyTank& enemyTank) {
    glm::vec3 directionToMainTank = glm::normalize(tankPosition - enemyTank.position);
    float rotationAngle = atan2(directionToMainTank.z, directionToMainTank.x) - glm::pi<float>();
    return rotationAngle;
}



bool Lab5::CheckCollisionWithBuilding(const glm::vec3& tankPosition, float tankRadius) {
    for (const auto& building : buildings) {;

        float distance = glm::distance(tankPosition, building.buildingPosition);
        if (distance < (tankRadius + buildingRadius)) {
            return true;
        }
    }
    return false;
}

bool Lab5::CheckCollisionWithEnemyTank(const glm::vec3& tankPosition, float tankRadius) {
    for (const auto& enemyTank : enemyTanks) {
        if (enemyTank.isAlive) {
            float distance = glm::distance(tankPosition, enemyTank.position);
            if (distance < (tankRadius + enemyTankRadius)) {
                return true;
            }
        }
    }
    return false;
}


void Lab5::RenderEnemyTank(EnemyTank& enemyTank) {
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, enemyTank.position);
    CalculateRotationAngleToFaceMainTank(enemyTank);
    float rotationAngle = CalculateRotationAngleToFaceMainTank(enemyTank);
    modelMatrix = glm::rotate(modelMatrix, rotationAngle, glm::vec3(0, 1, 0));

    RenderMesh(enemyTank.tankBody, shaders["Simple"], modelMatrix, enemyTank.currentColor);
    RenderMesh(enemyTank.tankTop, shaders["Simple"], modelMatrix, enemyTank.currentColor2);
    RenderMesh(enemyTank.tankGun, shaders["Simple"], modelMatrix, enemyTank.currentColor3);
    RenderMesh(enemyTank.tankWheels, shaders["Simple"], modelMatrix, enemyTank.currentColor3);
}


void Lab5::OnKeyRelease(int key, int mods)
{
    int x = 3;
    for (int i = 0; i < 3; i++) {
        if (key == GLFW_KEY_SPACE) {
            while (HP < 4) {
                HP++;
            }
        }
    }
}


void Lab5::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    float sensitivity = 0.001f;
    turretRotationAngle -= deltaX * sensitivity;
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;

        if (window->GetSpecialKeyState() == 0) {
            renderCameraTarget = false;
            camera->RotateFirstPerson_OX(-deltaY * sensivityOX);
            camera->RotateFirstPerson_OY(-deltaX * sensivityOY);
        }

        if (window->GetSpecialKeyState() & GLFW_MOD_CONTROL) {
            renderCameraTarget = true;
            camera->RotateThirdPerson_OX(-deltaY * sensivityOX);
            camera->RotateThirdPerson_OY(-deltaX * sensivityOY);
        }
    }
}

void Lab5::ShootBullet() {
    Bullet newBullet;
    newBullet.position = CalculateGunEndPosition();
    newBullet.velocity = CalculateBulletVelocity();
    newBullet.isActive = true;
    bullets.push_back(newBullet);
}

void Lab5::ShootEnemyBullet(EnemyTank& enemyTank) {
    enemyBullet newEnemyBullet;
    glm::vec3 directionToPlayer = glm::vec3(sin(enemyTank.rotationAngle), 0, cos(enemyTank.rotationAngle));
    newEnemyBullet.position = CalculateEnemyGunEndPosition(enemyTank);
    newEnemyBullet.velocity = directionToPlayer * newEnemyBullet.speed;

    newEnemyBullet.isActive = true;
    enemyBullets.push_back(newEnemyBullet);
}



void Lab5::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        ShootBullet();
    }
}


void Lab5::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}


void Lab5::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab5::OnWindowResize(int width, int height)
{
}

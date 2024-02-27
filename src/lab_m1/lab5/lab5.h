#pragma once

#include "components/simple_scene.h"
#include "lab_m1/lab5/lab_camera.h"


namespace m1
{
    class Lab5 : public gfxc::SimpleScene
    {
    public:
        Lab5();
        ~Lab5();

        void Init() override;


        //from lab6:
        Mesh* Lab5::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices);

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color = glm::vec3(1));

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void Lab5::ShootBullet();


        Mesh* Lab5::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices);


        struct EnemyTank {
            glm::vec3 position;
            Mesh* tankBody;
            Mesh* tankTop;
            Mesh* tankGun;
            Mesh* tankWheels;
            std::vector<EnemyTank> tanks;
            glm::mat4 modelMatrix;
            int enemyHP;
            glm::vec3 direction;
            float movementSpeed;
            float changeDirectionTime;
            float timeUntilChangeDirection;
            float timeSinceLastShot;
            float shootingInterval = 3.0f;
            float rotationAngle;
            float topRotationAngle;
            glm::vec3 topPosition;
            bool isCloseToPlayer;
            bool isAlive = true;
            glm::vec3 color;
            const glm::vec3 fullHPColor = glm::vec3(0.23, 0.28, 0.45); //bleumarin
            const glm::vec3 fullHPColor2 = glm::vec3(0.58, 0.66, 0.68); //griAlbastru
            const glm::vec3 fullHPColor3 = glm::vec3(0.45, 0.53, 0.68); //bleu
            glm::vec3 currentColor;
            glm::vec3 currentColor2;
            glm::vec3 currentColor3;
            float hpRatio;
        };
        std::vector<EnemyTank> enemyTanks;

        
        struct enemyBullet {
            glm::vec3 position;
            glm::vec3 velocity;
            bool isActive;
            float speed = 10;
            enemyBullet() : position(0), velocity(0), isActive(false) {}
        };
        std::vector<enemyBullet> enemyBullets;


        struct Bullet {
            glm::vec3 position;
            glm::vec3 velocity;
            bool isActive;
            Bullet() : position(0), velocity(0), isActive(false) {}
        };
        std::vector<Bullet> bullets;

        struct Building {
            glm::vec3 color = glm::vec3(1, 0.5, 0.7);
            glm::vec3 buildingPosition;
        };
        std::vector<Building> buildings;

        void Lab5::ShootEnemyBullet(EnemyTank& enemyTank);
        glm::vec3 CalculateGunDirection(float tankRotation, float turretRotation);
        void Lab5::RotateEnemyTankToFaceMainTank(EnemyTank& enemyTank);
        float Lab5::CalculateRotationAngleToFaceMainTank(const EnemyTank& enemyTank);
        void Lab5::RenderEnemyTank(EnemyTank& enemyTank);
        bool Lab5::CheckCollisionWithMainTank(const enemyBullet& enemyBullet);
        bool Lab5::CheckCollisionBulletEnemyTank(const Bullet& bullet, const EnemyTank& enemyTank);
        bool Lab5::CheckCollisionWithBuilding(const glm::vec3& tankPosition, float tankRadius);
        bool Lab5::CheckCollisionWithEnemyTank(const glm::vec3& tankPosition, float tankRadius);


    protected:
        implemented::Camera* camera;
        glm::mat4 projectionMatrix;
        bool renderCameraTarget;
        glm::vec3 tankPosition = glm::vec3(0, 1, 0);
        float tankRotationAngle = 90;
        float groundLevel = 0.5f;
        float turretRotationAngle = 0;
        float tankRadius = 2.0f;
        float buildingRadius = 1.0f;
        float enemyTankRadius = 2.0f;
        glm::mat4 modelMatrixBullet;
        int myHP = 5;
        float enemyTankRotationAngle;
        float EnemyTurretRotationAngle;
        int HP;

        glm::vec3 Lab5::CalculateBulletVelocity() {
            float bulletSpeed = 10.0f;
            float combinedRotation = -tankRotationAngle - turretRotationAngle;
            glm::vec3 bulletDirection = glm::normalize(glm::vec3(cos(combinedRotation), 0, sin(combinedRotation)));
            glm::vec3 bulletVelocity = bulletDirection * bulletSpeed;
            return bulletVelocity;
        }

        glm::vec3 Lab5::CalculateGunEndPosition() {
            float gunLength = 2.0f;
            float combinedRotation = -tankRotationAngle - turretRotationAngle;
            glm::vec3 gunDirection = glm::normalize(glm::vec3(cos(combinedRotation), 0, sin(combinedRotation)));
            glm::vec3 gunEndPosition = tankPosition + gunDirection * gunLength;
            return gunEndPosition;
        }
        
        glm::vec3 Lab5::CalculateEnemyBulletVelocity(EnemyTank& enemyTank) {
            float bulletSpeed = 10.0f;
            float combinedRotation = -enemyTank.rotationAngle - enemyTank.topRotationAngle;
            glm::vec3 bulletDirection = glm::normalize(glm::vec3(cos(combinedRotation), 0, sin(combinedRotation)));
            glm::vec3 bulletVelocity = bulletDirection * bulletSpeed;
            return bulletVelocity;
        }

        glm::vec3 Lab5::CalculateEnemyGunEndPosition(EnemyTank& enemyTank) {
            float EnemyGunLength = 2.0f;
            float combinedRotation = -enemyTank.rotationAngle -enemyTank.topRotationAngle;
            glm::vec3 EnemyGunDirection = glm::normalize(glm::vec3(cos(combinedRotation), 0, sin(combinedRotation)));
            glm::vec3 EnemyGunEndPosition = enemyTank.position + EnemyGunDirection * EnemyGunLength;
            return EnemyGunEndPosition;
        }
        void Lab5::RenderHPBar(const glm::vec3& tankPosition, float hpRatio, bool enemy) {
            float barWidth = 2.0f;\
            float barHeight = 0.1f;
            glm::vec3 barOffset(0.0f, 1.0f, 0.0f);
            glm::vec3 hpBarPosition = tankPosition + barOffset;
            glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), hpBarPosition);

            glm::vec3 hpColor;
            if (enemy) { hpColor = glm::vec3(0.8f, 0.0f, 0.0f);}
            else { hpColor = glm::vec3(0.0f, 0.8f, 0.0f); }

            modelMatrix = glm::scale(modelMatrix, glm::vec3(barWidth * hpRatio, barHeight, 1.0f));
            RenderMesh(meshes["square"], shaders["Simple"], modelMatrix, hpColor);
        }

        
        struct Cloud {
            glm::vec3 color = glm::vec3(0.99, 0.9, 0.9);
            glm::vec3 cloudPosition;
        };
        std::vector<Cloud> clouds;

        struct Grass {
            glm::vec3 color = glm::vec3(0.2, 0.8, 0.2);
            glm::vec3 grassPosition;
        };
        std::vector<Grass> grassPatches;

        struct Flower {
            glm::vec3 color = glm::vec3(1, 0.2, 0.2);
            glm::vec3 flowerPosition;
        };
        std::vector<Flower> flowers;


        glm::vec3 lightPosition;
        unsigned int materialShininess;
        float materialKd;
        float materialKs;

        glm::vec3 bleumarin = glm::vec3(0.23, 0.28, 0.45);
        glm::vec3 griAlbastru = glm::vec3(0.58, 0.66, 0.68);
        glm::vec3 bleu = glm::vec3(0.45, 0.53, 0.68);
        glm::vec3 rodie = glm::vec3(0.6, 0.15, 0.3);
        glm::vec3 ametist = glm::vec3(0.49, 0.44, 0.73);
        glm::vec3 somon = glm::vec3(1, 0.64, 0.65);
        glm::vec3 somonTop = glm::vec3(0.8, 0.35, 0.5);

        const int maxEnemyHP = 3; 
        const int maxHP = 3; 
        const glm::vec3 fullHPColor = somonTop;
        const glm::vec3 fullHPColor2 = somon; 
        const glm::vec3 fullHPColor3 = rodie;
        const glm::vec3 zeroHPColor = glm::vec3(0.2f, 0.2f, 0.2f);

    };
}

#ifndef Tasks_h
#define Tasks_h

#include "RubiksCube.h"
#include "../Transform.h"

#include <string>

class FaceRotation : public RubiksCube::ITask {
public:
    FaceRotation(RubiksCube& owner, RubiksCube::Face& face, RubiksCube::ERotation rotation, float target_angle, float speed = 1.0f)
        : m_Owner(owner)
        , m_Face(face)
        , m_Rotation(rotation)
        , m_TargetAngle(target_angle * static_cast<int>(rotation))
        , m_RotationSpeed(speed)
        , m_Signature(face.Siganture)
        , m_Progress(0.0f)
        , m_Finished(false) {

        if (rotation == RubiksCube::ERotation::COUNTER_CLOCKWISE) {
            m_Signature.append("'");
        }
    }

    bool Finished() const override { return m_Finished; }

    std::string Signature() const override { return m_Signature; }

    void Progress(float delta) override {
        // Task already finished
        if (m_Finished) {
            return;
        }

        const float new_angle = m_RotationSpeed * delta * m_TargetAngle;
        if (abs(m_Progress + new_angle) > abs(m_TargetAngle)) {
            // On task finished
            RotateMeshes(m_TargetAngle - m_Progress);
            RotateData();
            m_Finished = true;
        } else {
            // Continue on task
            m_Progress = m_Progress + new_angle;
            RotateMeshes(new_angle);
        }
    }

private:
    void RotateMeshes(float angle) {
        for (int i = 0; i < 8; i++) {
            m_Owner.m_Cube[m_Face.CubiesAround[i][0]][m_Face.CubiesAround[i][1]][m_Face.CubiesAround[i][2]]->RotateAround(angle, m_Face.Axis);
        }
        m_Owner.m_Cube[m_Face.Center[0]][m_Face.Center[1]][m_Face.Center[2]]->RotateAround(angle, m_Face.Axis);
    }

    void RotateData() {
        // GCD left-shift array shift
        const int size = 8;
        const int shift = m_Rotation == RubiksCube::ERotation::CLOCKWISE ? 6 : 2;   // For clockwise rotation right-shift by 2 is equal to left-shift by 6. For counter clockwise rotation left-shift by 2.
        const int gcd = 2;                                                          // gcd(2, 8) = gcd(6, 8) = 2
        for (int i = 0; i < gcd; i++) {
            Cubie* tmp = m_Owner.m_Cube[m_Face.CubiesAround[i][0]][m_Face.CubiesAround[i][1]][m_Face.CubiesAround[i][2]];
            int j = i;

            while (true) {
                int k = j + shift;
                if (k >= size) {
                    k = k - size;
                }
                if (k == i) {
                    break;
                }

                m_Owner.m_Cube[m_Face.CubiesAround[j][0]][m_Face.CubiesAround[j][1]][m_Face.CubiesAround[j][2]] = m_Owner.m_Cube[m_Face.CubiesAround[k][0]][m_Face.CubiesAround[k][1]][m_Face.CubiesAround[k][2]];
                j = k;
            }
            m_Owner.m_Cube[m_Face.CubiesAround[j][0]][m_Face.CubiesAround[j][1]][m_Face.CubiesAround[j][2]] = tmp;
        }
    }

    RubiksCube& m_Owner;
    RubiksCube::Face& m_Face;
    RubiksCube::ERotation m_Rotation;
    float m_TargetAngle;
    float m_RotationSpeed;
    std::string m_Signature;

    float m_Progress;
    bool m_Finished;
};



class CubeRotation : public RubiksCube::ITask {
public:
    CubeRotation(RubiksCube& owner, Transform* transform, RubiksCube::EDirection direction, RubiksCube::ERotation rotation, float speed = 1.0f) 
        : m_Owner(owner)
        , m_Transform(transform)
        , m_Direction(direction)
        , m_Rotation(rotation)
        , m_TargetAngle(glm::radians(90.0f) * static_cast<int>(rotation))
        , m_RotationSpeed(speed)
        , m_Signature()
        , m_Progress(0.0f)
        , m_Finished(false) {
        if (direction == RubiksCube::EDirection::FRONT) {
            m_RotationAxis = glm::vec3(1.0f, 0.0f, 0.0);
        } else if (direction == RubiksCube::EDirection::UP) {
            m_RotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
        } else if (direction == RubiksCube::EDirection::RIGHT) {
            // Since cube's front is aligned with X axis, it's right is on the negative Z axis
            m_RotationAxis = glm::vec3(0.0f, 0.0f, -1.0);
        }

        m_Signature += static_cast<char>(direction);
        if (rotation == RubiksCube::ERotation::COUNTER_CLOCKWISE) {
            m_Signature.append("'");
        }
    }

    bool Finished() const override { return m_Finished; }

    std::string Signature() const override { return m_Signature; }

    void Progress(float delta) override {
        if (m_Finished) {
            return;
        }

        const float new_angle = m_RotationSpeed * delta * m_TargetAngle;
        if (abs(m_Progress + new_angle) > abs(m_TargetAngle)) {
            // On task finished
            m_Transform->Rotate(m_RotationAxis * new_angle);
            RotateData();
            m_Finished = true;
        } else {
            // Continue on task
            m_Progress = m_Progress + new_angle;
            m_Transform->Rotate(m_RotationAxis * new_angle);
        }
    }

private:
    void RotateData() {
        if (m_Direction == RubiksCube::EDirection::RIGHT) {
            if (m_Rotation == RubiksCube::ERotation::COUNTER_CLOCKWISE) {
                SwapFaces(m_Owner.m_Up, m_Owner.m_Front);
                SwapFaces(m_Owner.m_Up, m_Owner.m_Down);
                SwapFaces(m_Owner.m_Up, m_Owner.m_Back);
            } else {
                SwapFaces(m_Owner.m_Up, m_Owner.m_Back);
                SwapFaces(m_Owner.m_Up, m_Owner.m_Down);
                SwapFaces(m_Owner.m_Up, m_Owner.m_Front);
            }
        } else if (m_Direction == RubiksCube::EDirection::UP) {
            if (m_Rotation == RubiksCube::ERotation::COUNTER_CLOCKWISE) {
                SwapFaces(m_Owner.m_Front, m_Owner.m_Right);
                SwapFaces(m_Owner.m_Front, m_Owner.m_Back);
                SwapFaces(m_Owner.m_Front, m_Owner.m_Left);
            } else {
                SwapFaces(m_Owner.m_Front, m_Owner.m_Left);
                SwapFaces(m_Owner.m_Front, m_Owner.m_Back);
                SwapFaces(m_Owner.m_Front, m_Owner.m_Right);
            }
        } else if (m_Direction == RubiksCube::EDirection::FRONT) {
            if (m_Rotation == RubiksCube::ERotation::COUNTER_CLOCKWISE) {
                SwapFaces(m_Owner.m_Up, m_Owner.m_Left);
                SwapFaces(m_Owner.m_Up, m_Owner.m_Down);
                SwapFaces(m_Owner.m_Up, m_Owner.m_Right);
            } else {
                SwapFaces(m_Owner.m_Up, m_Owner.m_Right);
                SwapFaces(m_Owner.m_Up, m_Owner.m_Down);
                SwapFaces(m_Owner.m_Up, m_Owner.m_Left);
            }
        }
    }

    void SwapFaces(RubiksCube::Face& lhs, RubiksCube::Face& rhs) {
        std::swap(lhs.CubiesAround, rhs.CubiesAround);
        std::swap(lhs.Center, rhs.Center);
        std::swap(lhs.Axis, rhs.Axis);
    }

    RubiksCube& m_Owner;
    Transform* m_Transform;
    RubiksCube::EDirection m_Direction;
    RubiksCube::ERotation m_Rotation;
    glm::vec3 m_RotationAxis;
    float m_TargetAngle;
    float m_RotationSpeed;
    std::string m_Signature;

    float m_Progress;
    bool m_Finished;
};

#endif

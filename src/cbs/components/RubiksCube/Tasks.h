#ifndef Tasks_h
#define Tasks_h

#include "RubiksCube.h"

#include <string>

class FaceRotation : public RubiksCube::ITask {
public:
    FaceRotation(RubiksCube& owner, const RubiksCube::Face& face, float target_angle, const std::string& signature, float speed = 1.0f)
        : m_Owner(owner)
        , m_Face(face)
        , m_TargetAngle(target_angle)
        , m_Signature(signature)
        , m_RotationSpeed(speed)
        , m_Progress(0.0f)
        , m_Finished(false) {}

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
            m_Owner.RotateMeshes(m_Face, m_TargetAngle - m_Progress);
            m_Owner.RotateData(m_Face, m_TargetAngle < 0.0f ? RubiksCube::ERotation::CLOCKWISE : RubiksCube::ERotation::COUNTER_CLOCKWISE);
            m_Finished = true;
        } else {
            // Continue on task
            m_Progress = m_Progress + new_angle;
            m_Owner.RotateMeshes(m_Face, new_angle);
        }
    }

private:
    RubiksCube& m_Owner;
    const RubiksCube::Face& m_Face;
    float m_TargetAngle;
    std::string m_Signature;
    float m_RotationSpeed;

    float m_Progress;
    bool m_Finished;
};

#endif

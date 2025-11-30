#ifndef BALLHANDLER_H
#define BALLHANDLER_H

#include "TriangleSurface.h"
#include <QVector3D>
#include <qdebug.h>

class TriangleSurface;

// We'll need a ball struct, because every ball will be individual

struct BallHandler
{
public:
    BallHandler();
    std::vector<QVector3D> mPosition;
    std::vector<QVector3D> mVelocity;
    std::vector<float> mRadius;
    std::vector<float> mMass;

    int addBall(const QVector3D& position, const QVector3D& velocity, float radius, float mass){
        mPosition.push_back(position);
        mVelocity.push_back(velocity);
        mRadius.push_back(radius);
        mMass.push_back(mass);
        return static_cast<int>(mPosition.size()) - 1; // ball ID
    };

    void updatePosition(float dt, const TriangleSurface* terrain){

        // No idea how to include it outside of the function without it failing, so it stays here.

        const QVector3D gravity(0.0f, -9.81f, 0.0f);
        const float my = 0.5f;   // friction coef. for 2.3

        for (size_t i = 0; i < mPosition.size(); ++i)
        {
            // Apply gravitational acceleration F = m*g
            mVelocity[i] += mMass[i] * gravity * dt;
            mPosition[i]  += mVelocity[i] * dt;

            if (!terrain)
                mVelocity[i] = QVector3D(0,0,0);
                mPosition[i] = QVector3D(0,-0.5,0);
                continue; // Need to write a code for what to do when the ball is off the ground;
            // Most likely going to work with an object pool so that the generated balls are re-used to spawn more balls once they roll off the edge..

            QVector3D normal(0.0f, 1.0f, 0.0f);
            float h = sampleHeightNeighbour(terrain, mPosition[i], &normal);
            normal.normalize();

            float ground_height = h + mRadius[i];
            if (mPosition[i].y() < ground_height){ mPosition[i].setY(ground_height);};


            float gN = QVector3D::dotProduct(gravity, normal);
            QVector3D a_normal  = gN * normal;
            QVector3D a_tangent = gravity - a_normal;


            // Compute gravity with normals:
            QVector3D v = mVelocity[i];
            float vN = QVector3D::dotProduct(v, normal);
            QVector3D v_normal  = vN * normal;
            QVector3D v_tangent = v - v_normal;
            QVector3D a_friction(0.0f, 0.0f, 0.0f);


            float speedT = v_tangent.length();
            if (speedT > 0.0001f)
            {
                QVector3D t_hat = v_tangent / speedT;
                float N_mag = std::fabs(gN);
                a_friction = -my * N_mag * t_hat;
            }

            QVector3D a = a_tangent + a_friction;

            mVelocity[i] += a * dt;
            mPosition[i] += mVelocity[i] * dt;

            //Make sure that the ball doesn't clip through the ground.
            float newY = sampleHeightNeighbour(terrain, mPosition[i], &normal);
            mPosition[i].setY(newY + mRadius[i]);

        }
    };

    // Find nearest vertex, sample height, return Normal
    static float sampleHeightNeighbour(const TriangleSurface* terrain, const QVector3D& coordinates, QVector3D* returnNormal)
    {
        const auto& verts   = terrain->getVertices();
        const auto& normals = terrain->getNormals();

        // In case there's nothing to sample :
        if (verts.empty())
        {
            if (returnNormal)
                *returnNormal = QVector3D(0.0f, 1.0f, 0.0f);
            qDebug()<< "Vertixes empty, returning " << returnNormal << "instead.";
            return 0.0f;
        }

        float bestDistance   = 10000000.0f;
        float bestHeight  = verts[0].y;         // y of the closest vertex
        QVector3D bestNormal(0.0f, 1.0f, 0.0f); // normal of the closest vertex

        for (size_t i = 0; i < verts.size(); ++i)
        {
            const Vertex& v = verts[i];

            // distance in xz-plane from ball to vertex
            float dx = v.x - coordinates.x();
            float dz = v.z - coordinates.z();
            float dist = dx*dx + dz*dz;

            if (dist < bestDistance)
            {
                bestDistance  = dist;
                bestHeight = v.y;

                if (i < normals.size())
                    bestNormal = normals[i];
            }
        }

        if (returnNormal)
            *returnNormal = bestNormal.normalized();

        return bestHeight;
    };

};

#endif // BALLHANDLER_H

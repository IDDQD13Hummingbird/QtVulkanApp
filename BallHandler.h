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

    void mDirectionDebug(int i){
        if (mVelocity[i].x()< 0 && mVelocity[i].z()<0){qDebug()<<"Left-Down, ";}
        else if (mVelocity[i].x()< 0 && mVelocity[i].z()>0){qDebug()<<"Left-Up, ";}
        else if (mVelocity[i].x()> 0 && mVelocity[i].z()<0){qDebug()<<"Right-Down, ";}
        else if (mVelocity[i].x()> 0 && mVelocity[i].z()>0){qDebug()<<"Right-Up, ";}
        else if (mVelocity[i].x()< 0 && mVelocity[i].z()==0){qDebug()<<"Left, ";}
        else if (mVelocity[i].x()> 0 && mVelocity[i].z()==0){qDebug()<<"Right, ";}
        else if (mVelocity[i].x()== 0 && mVelocity[i].z()<0){qDebug()<<"Down, ";}
        else if (mVelocity[i].x()== 0 && mVelocity[i].z()>0){qDebug()<<"Up, ";}
        else{qDebug()<<"Moving ";};

        if(mVelocity[i].y()< 0){qDebug()<<"Falling \n";}
        else{qDebug()<<"Going up \n";};
    }

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

        //herding balls :
        const float inContact_Distance = 0.15f;
        const float maxSupportDist = 0.5f;


        for (size_t i = 0; i < mPosition.size(); ++i)
        {
            // Apply gravitational acceleration F = m*g
            mVelocity[i] += /*mMass[i] * */ gravity * dt;
            mPosition[i]  += mVelocity[i] * dt;

            if (!terrain){
                mVelocity[i] = QVector3D(0,0,0);
                mPosition[i] = QVector3D(0,-0.5,0);
                continue;} // Need to write a code for what to do when the ball is off the ground;
            // Most likely going to work with an object pool so that the generated balls are re-used to spawn more balls once they roll off the edge..

            QVector3D normal(0.0f, 1.0f, 0.0f);
            float dist = 0;
            int nearIndex = -1;
            float h = sampleHeightNeighbour(terrain, mPosition[i], &normal, &dist, &nearIndex);
            normal.normalize();

            bool onGround = (dist < maxSupportDist);
            float ground_height = h + mRadius[i];

            QVector3D a(0.0f, 0.0f, 0.0f);

            if (onGround && mPosition[i].y() < ground_height + inContact_Distance){
                mPosition[i].setY(ground_height);};

            float my = 0.5f;   // friction coef. for 2.3; gets reassigned depending on the terrain underneath.
            if (nearIndex >= 0) {
                const auto& friction = terrain->getFriction();
                if (nearIndex < (static_cast<int>(friction.size()))){
                    my = friction[nearIndex];}
            }

            if (onGround && mPosition[i].y() <= ground_height + inContact_Distance)
            {
                // -------- CONTACT MODE (ball on the terrain) --------

                // Keep ball on the surface
                mPosition[i].setY(ground_height);

                // Decompose gravity into normal + tangent
                float gN = QVector3D::dotProduct(gravity, normal); // should be negative
                QVector3D g_normal  = gN * normal;
                QVector3D g_tangent = gravity - g_normal;          // along the surface

                // Decompose velocity into normal + tangent
                float vN = QVector3D::dotProduct(mVelocity[i], normal);
                QVector3D v_normal  = vN * normal;
                QVector3D v_tangent = mVelocity[i] - v_normal;

                // Kill any velocity that tries to sink ball into the ground
                if (vN < 0.0f)
                    mVelocity[i] -= v_normal;

                // Friction opposite to tangent velocity
                QVector3D a_friction(0,0,0);
                float speedT = v_tangent.length();
                if (speedT > 0.0001f)
                {
                    QVector3D t_hat = v_tangent / speedT;
                    float N_mag = -gN;
                    a_friction = - my * N_mag * t_hat;
                }

                // Net acceleration along the surface
                a = g_tangent + a_friction;
            }
            else if (onGround)
            {
                // -------- ABOVE MESH --------
                a = gravity;
            }
            else
            {
                // -------- OUT OF BOUNDS --------
                mVelocity[i] = QVector3D(0, 0, 0);
                // keep last position, do not snap to any height
                continue;
            }

            // Integrate with the chosen acceleration
            mVelocity[i] += a * dt;
            mPosition[i] += mVelocity[i] * dt;

            // Small correction: if we penetrated the ground after integration, snap back
            if (onGround)
            {
                QVector3D n;
                float temp1;
                int temp2;
                float h = sampleHeightNeighbour(terrain, mPosition[i], &n, &temp1, &temp2);
                float ground_height = h + mRadius[i];
                if (mPosition[i].y() < ground_height)
                    mPosition[i].setY(ground_height);
            }
    };

 };

    // Find nearest vertex, sample height, return Normal
    static float sampleHeightNeighbour(const TriangleSurface* terrain, const QVector3D& coordinates, QVector3D* returnNormal, float* out_of_bounds, int* returnIndex)
    {
        const auto& verts = terrain->getVertices();
        const auto& normals = terrain->getNormals();

        // In case there's nothing to sample :
        if (verts.empty())
        {
            if (returnNormal){
                *returnNormal = QVector3D(0.0f, 1.0f, 0.0f);
            qDebug()<< "Vertixes empty, returning " << returnNormal << "instead.";
            }
            if (out_of_bounds)
                *out_of_bounds = std::numeric_limits<float>::max();
            return 0.0f;
            if (returnIndex){
                *returnIndex = -1;
            };
            return 0.0f;
        }

        // Need to adjust for the actual position in engine

        QMatrix4x4 Terrain = terrain->getMatrix();
        QVector3D offset = Terrain.column(3).toVector3D();
        QVector3D local_coordinates = coordinates - offset;

        float bestDistance = 10000.0f;
        float bestHeight = verts[0].y; // y of the closest vertex
        QVector3D bestNormal(0.0f, 1.0f, 0.0f); // normal of the closest vertex
        int bestIndex = 0; // index of the closest vertex

        for (size_t i = 0; i < verts.size(); ++i)
        {
            const Vertex& v = verts[i];

            // distance in x z plane from ball to vertex
            float dx = v.x - local_coordinates.x();
            float dz = v.z - local_coordinates.z();
            float dist = dx*dx + dz*dz;

            if (dist < bestDistance)
            {
                bestDistance  = dist;
                bestHeight = v.y;
                bestIndex  = static_cast<int>(i);

                if (i < normals.size())
                    bestNormal = normals[i];
            }
        }

        if (returnNormal){*returnNormal = bestNormal.normalized();};
        if (out_of_bounds){*out_of_bounds = bestDistance;};
        if (returnIndex){*returnIndex = bestIndex;};

        return bestHeight + offset.y(); //translated for the world space.
    };

};
#endif // BALLHANDLER_H

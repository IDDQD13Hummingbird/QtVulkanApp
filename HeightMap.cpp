#include "HeightMap.h"
#include "Vertex.h"
#include "stb_image.h"

HeightMap::HeightMap()
{ }

void HeightMap::makeTerrain(std::string heightMapImage)
{
    //Load the heightmap image
    //Using stb_image to load the image
    stbi_uc* pixelData = stbi_load(heightMapImage.c_str(), &mWidth, &mHeight, &mChannels, STBI_rgb_alpha);
    if (pixelData == nullptr)
    {
        //qDebug() << "Failed to load heightmap image!";
        return;
    }
    //Make the terrain from the pixel data
    //qDebug() << "width was changed: " << mWidth;
    makeTerrain(pixelData, mWidth, mHeight);
    //qDebug() << "width was changed: " << mWidth;
    stbi_image_free(pixelData);
}

//Function that makes a terrain grid from a heightmap, using the values in the heightmap as height.
//This function will crash if the width and height of the heightmap is not set correct!
//The size of the textureData array is widthIn * heightIn.
// The function is not tested in this codebase, and is provided as an example.
void HeightMap::makeTerrain(unsigned char* textureData, int widthIn, int heightIn)
{
    //Default normal pointing straight up - should be calculated correctly for lights to work!!!
    float normal[3]{0.f, 1.f, 0.f};

    //How many meters(units) between each vertex in both x and z direction
    //This should be sent in as a parameter!
    float horisontalSpacing{.2f};

    //Scaling the height read from the heightmap. 0 -> 255 meters(units) if this is set to 1
    //This should be sent in as a parameter!
    float heightSpacing{.02f};

    //Offset the whole terrain in y (height) axis
    //Moves the terrain mesh up or down
    //Because of Barycentric calculations, we want the terrain to be in World coordinates!
    //So we don't want to move the terrain up or down in the Y axis after it is made
    float heightPlacement{-5.f};

    //Getting the scale of the heightmap
    //Using depth as the name of texture height, to not confuse with terrain height
    unsigned short width = widthIn;       //Width == x-axis
    unsigned short depth = heightIn;      //Depth == z-axis

    //qDebug() << "width was changed: " << widthIn;

    //Temp variables for creating the mesh
    //Adding offset so the middle of the terrain will be in World origo
    float vertexXStart{ 0.f - width * horisontalSpacing / 2 };            // if world origo should be at center use: {0.f - width * horisontalSpacing / 2};
    float vertexZStart{ 0.f + depth * horisontalSpacing / 2 };            // if world origo should be at center use: {0.f + depth * horisontalSpacing / 2};

    //saafloat vertexXStart{ 0.f };
    //saafloat vertexZStart{ 0.f };

    //Loop to make the mesh from the values read from the heightmap (textureData)
    //Double for-loop to make the depth and the width of the terrain in one go
    for(int d{0}; d < depth; ++d)       //depth loop
    {
        for(int w{0}; w < width; ++w)   //width loop
        {
            //Heightmap image is actually stored as an one dimentional array - so calculating the correct index for column and row
            //and scale it according to variables
            // Calculate the correct index for the R value of each pixel
            int index = (w + d * width) * 4; // Each pixel has 4 bytes (RGBA)
            float heightFromBitmap = static_cast<float>(textureData[index]) * heightSpacing + heightPlacement;
            //                                          x - value                      y-value               z-value
            mVertices.emplace_back(Vertex{vertexXStart + (w * horisontalSpacing), heightFromBitmap, vertexZStart - (d * horisontalSpacing),
                                          //  dummy normal=0,1,0                  Texture coordinates
                                          normal[0],normal[1],normal[2],           w / (width - 1.f), d / (depth - 1.f), 0});
        }
    }

    //qDebug() << "width was changed: " << width;
    // The mesh(grid) is drawn in quads with diagonals from lower left to upper right
    //          _ _
    //         |/|/|
    //          - -
    //         |/|/|
    //          - -
    //Making the indices for this mesh:
    for(int d{0}; d < depth-1; ++d)        //depth - 1 because we draw the last quad from depth - 1 and in negative z direction
    {
        for(int w{0}; w < width-1; ++w)    //width - 1 because we draw the last quad from width - 1 and in positive x direction
        {
            //Indices for one quad:
            mIndices.emplace_back(w + d * width);               // 0 + 0 * mWidth               = 0
            mIndices.emplace_back(w + d * width + width + 1);   // 0 + 0 * mWidth + mWidth + 1  = mWidth + 1
            mIndices.emplace_back(w + d * width + width);       // 0 + 0 * mWidth + mWidth      = mWidth
            mIndices.emplace_back(w + d * width);               // 0 + 0 * mWidth               = 0
            mIndices.emplace_back(w + d * width + 1);           // 0 + 0 * mWidth + 1           = 1
            mIndices.emplace_back(w + d * width + width + 1);   // 0 + 0 * mWidth + mWidth + 1  = mWidth + 1
        }
    }

    //qDebug() << "width was changed: " << width;

    //Calculating the normals for the mesh
    //Function not made yet:
    //calculateHeighMapNormals();
}

float HeightMap::calculateBarycentric(const QVector2D& P, const QVector3D& A, const QVector3D& B, const QVector3D& C)
{
    // transferring values to 2D vectors
    QVector2D a(A.x(), A.z());
    QVector2D b(B.x(), B.z());
    QVector2D c(C.x(), C.z());

    QVector2D v0 = b - a, v1 = c - a, v2 = P - a;

    float d00 = QVector2D::dotProduct(v0, v0);
    float d01 = QVector2D::dotProduct(v0, v1);
    float d11 = QVector2D::dotProduct(v1, v1);
    float d20 = QVector2D::dotProduct(v2, v0);
    float d21 = QVector2D::dotProduct(v2, v1);

    float denom = d00 * d11 - d01 * d01;
    if(denom == 0.f)
        return a.y(); // avoid dividing by 0

    // Barycentric coordinates
    float v = (d11 * d20 - d01 * d21) / denom;
    float w = (d00 * d21 - d01 * d20) / denom;
    float u = 1 - v - w; // u + v + w = 1

    //qDebug() << "A: " << A.y() << ", B: " << B.y() << ", C: " << C.y();
    //qDebug() << "uA: " << u * A.y() << ", vB: " << v * B.y() << ", wC: " << w * C.y();
    //qDebug() << "result: " << u * A.y() + v * B.y() + w * C.y();

    //qDebug() << "B: " << B.y();
    //qDebug() << "C: " << C.y();
    //qDebug() << "u: " << u << ", v: " << v << ", w: " << w;
    return u * A.y() + v * B.y() + w * C.y();
}

float HeightMap::getHeightOnMap(float worldX, float worldZ, std::vector<Vertex> mapVertices)
{
    //qDebug() << "Width: " << mWidth;
    float horizontalSpacing{0.2f};

    float offsetX = -mWidth * horizontalSpacing / 2.0f;
    float offsetZ = +mHeight * horizontalSpacing / 2.0f;

    // Convert world coords to grid coords
    float localX = worldX - offsetX;
    float localZ = -(worldZ - offsetZ); // flipped due to terrain growing downward in Z

    int gridX = static_cast<int>(localX / horizontalSpacing);
    int gridZ = static_cast<int>(localZ / horizontalSpacing);

    if (gridX < 0 || gridZ < 0 || gridX >= mWidth - 1 || gridZ >= mHeight - 1)
        return 0.0f;

    float xCoord = fmod(localX, horizontalSpacing) / horizontalSpacing;
    float zCoord = fmod(localZ, horizontalSpacing) / horizontalSpacing;

    //int gridX = static_cast<int>(worldX / horizontalSpacing); // EDIT THESE TWO TO GET CORRECT HEIGHTMAP
    //int gridZ = static_cast<int>(-worldZ / horizontalSpacing);

    //qDebug() << "Grid X: " << gridX;
    //qDebug() << "Grid Z: " << gridZ;

    // Make out of bounds checker here

    //float xCoord = fmod( worldX, horizontalSpacing) / horizontalSpacing;
    //float zCoord = fmod(-worldZ, horizontalSpacing) / horizontalSpacing;

    QVector3D a, b, c;

    int topLeftIndex = gridX + gridZ * mWidth;

    if (xCoord + zCoord <= 1.0f)
    {
        // Upper-left triangle
        a = QVector3D(mVertices[topLeftIndex].x, mVertices[topLeftIndex].y, mVertices[topLeftIndex].z);
        b = QVector3D(mVertices[topLeftIndex + 1].x, mVertices[topLeftIndex + 1].y, mVertices[topLeftIndex + 1].z);
        c = QVector3D(mVertices[topLeftIndex + mWidth].x, mVertices[topLeftIndex + mWidth].y, mVertices[topLeftIndex + mWidth].z);
    }
    else
    {
        // Lower-right triangle
        a = QVector3D(mVertices[topLeftIndex + 1 + mWidth].x, mVertices[topLeftIndex + 1 + mWidth].y, mVertices[topLeftIndex + 1 + mWidth].z);
        b = QVector3D(mVertices[topLeftIndex + mWidth].x, mVertices[topLeftIndex + mWidth].y, mVertices[topLeftIndex + mWidth].z);
        c = QVector3D(mVertices[topLeftIndex + 1].x, mVertices[topLeftIndex + 1].y, mVertices[topLeftIndex + 1].z);
    }

    //qDebug() << "mVertices size: " << mapVertices.size();
    //qDebug() << "vertex XZ: " << mVertices[gridX].x << ", " << mVertices[gridX].z;
    //qDebug() << "mapVertex: " << mapVertices[topLeftIndex].x;
    //qDebug() << "Grid X: " << gridX;
    //qDebug() << "Grid Z: " << gridZ;
    //qDebug() << "Width: " << mWidth;
    //qDebug() << "top left index: " << topLeftIndex;

    //qDebug() << "X coordinate: " << xCoord << ", Z coordinate: " << zCoord;
    //if(xCoord + zCoord <= 1.f)
    //{
    //    // PROBLEM LIES HERE, VECTORS ARE OUT OF RANGE
    ////    // Top-Left triangle
    //    //qDebug() << "top left index: " << topLeftIndex;
    //    //qDebug() << "Grid X: " << gridX;
    //    //qDebug() << "Grid Z: " << gridZ;
    //    //qDebug() << "vertices: " << mVertices[topLeftIndex].x << mVertices[topLeftIndex].z;
    //    a = QVector3D(mapVertices[topLeftIndex].x, mapVertices[topLeftIndex].y, mapVertices[topLeftIndex].z);
    //    b = QVector3D(mapVertices[topLeftIndex + 1].x, mapVertices[topLeftIndex + 1].y, mapVertices[topLeftIndex + 1].z);
    //    c = QVector3D(mapVertices[topLeftIndex + mWidth].x, mapVertices[topLeftIndex + mWidth].y, mapVertices[topLeftIndex + mWidth].z);
    //    //qDebug() << "top left a: " << a;
    //}
    //else
    //{
    //    //qDebug("bottom right triangle used!");
    //    // Bottom-Right triangle
    //    a = QVector3D(mapVertices[topLeftIndex + 1 + mWidth].x, mapVertices[topLeftIndex + 1 + mWidth].y, mapVertices[topLeftIndex + 1 + mWidth].z);
    //    b = QVector3D(mapVertices[topLeftIndex + mWidth].x, mapVertices[topLeftIndex + mWidth].y, mapVertices[topLeftIndex + mWidth].z);
    //    c = QVector3D(mapVertices[topLeftIndex + 1].x, mapVertices[topLeftIndex + 1].y, mapVertices[topLeftIndex + 1].z);
    //    //qDebug() << "bottom right a: " << a;
    //}

    //a = QVector3D(mapVertices[topLeftIndex].x, mapVertices[topLeftIndex].y, mapVertices[topLeftIndex].z);
    //b = QVector3D(mapVertices[topLeftIndex + 1].x, mapVertices[topLeftIndex + 1].y, mapVertices[topLeftIndex + 1].z);
    //c = QVector3D(mapVertices[topLeftIndex + mWidth].x, mapVertices[topLeftIndex + mWidth].y, mapVertices[topLeftIndex + mWidth].z);

    //qDebug() << "Grid X: " << gridX;
    //qDebug() << "Grid Z: " << gridZ;

    return calculateBarycentric(QVector2D(worldX, worldZ), a, b, c);
}

#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(1.5f * length, 0, 0), color),
        VertexFormat(corner + glm::vec3(1.5f * length, 1.5f * length, 0), color),
        VertexFormat(corner + glm::vec3(0, 1.5f * length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateLife(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color), // 0
        VertexFormat(corner + glm::vec3(-1 * length, 1 * length, 0), color), // 1
         VertexFormat(corner + glm::vec3(-1 * length, -1 * length, 0), color), // 2
        VertexFormat(corner + glm::vec3(1 * length, -1 * length, 0), color), // 3
        VertexFormat(corner + glm::vec3(1 * length, 1 * length, 0), color) //4
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 0, 2, 3, 0, 3, 4, 0, 4, 1 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateRectangle(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(1.5f * length, 0, 0), color),
        VertexFormat(corner + glm::vec3(1.5f * length, 5.6f * length, 0), color),
        VertexFormat(corner + glm::vec3(0, 5.6f * length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateHexa(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;
    glm::vec3 color2 = glm::vec3(0, 1, 0);

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color), // 0
        VertexFormat(corner + glm::vec3(0, 0.4f * length, 1), color), // 1
        VertexFormat(corner + glm::vec3(-0.4f * length, 0.2f * length, 1), color), // 2
        VertexFormat(corner + glm::vec3(-0.4f * length, 0, 1), color), // 3
        VertexFormat(corner + glm::vec3(-0.4f * length, -0.2f * length, 1), color), // 4
        VertexFormat(corner + glm::vec3(0, -0.4f * length, 1), color), // 5
        VertexFormat(corner + glm::vec3(0.4f * length, -0.2f * length, 1), color),  // 6
        VertexFormat(corner + glm::vec3(0.4f * length, 0, 1), color), // 7
        VertexFormat(corner + glm::vec3(0.4f * length, 0.2f * length, 1), color),  // 8
        VertexFormat(corner, color2), // 9
        VertexFormat(corner + glm::vec3(0, 0.25f * length, 1), color2), // 10
        VertexFormat(corner + glm::vec3(-0.25f * length, 0.15f * length, 1), color2), // 11
        VertexFormat(corner + glm::vec3(-0.25f * length, 0, 1), color2), // 12
        VertexFormat(corner + glm::vec3(-0.25f * length, -0.15f * length, 1), color2), // 13
        VertexFormat(corner + glm::vec3(0, -0.25f * length, 1), color2), // 14
        VertexFormat(corner + glm::vec3(0.25f * length, -0.15f * length, 1), color2),  // 15
        VertexFormat(corner + glm::vec3(0.25f * length, 0, 1), color2), // 16
        VertexFormat(corner + glm::vec3(0.25f * length, 0.15f * length, 1), color2), // 17

    };

  Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 0, 2, 3, 0, 3, 4, 0, 4, 5, 0, 5, 6, 0, 6, 7, 0, 7, 8, 0, 8, 1, 
                                        9, 10, 11, 9, 11, 12, 9, 12, 13, 9, 13, 14, 9, 14, 15, 9, 15, 16, 9, 16, 17, 9, 17, 10};

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateDiamond(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color), // 0
        VertexFormat(corner + glm::vec3(0.4f * length, 0, 3), color), // 1
        VertexFormat(corner + glm::vec3(0.2f * length, 0.2f * length, 3), color), // 2
        VertexFormat(corner + glm::vec3(0, 0.4f * length, 3), color), // 3
        VertexFormat(corner + glm::vec3(-0.2f * length, 0.2f * length, 3), color), // 4
        VertexFormat(corner + glm::vec3(-0.4f * length, 0, 3), color), // 5
        VertexFormat(corner + glm::vec3(-0.2f * length, -0.2f * length, 3), color), // 6
        VertexFormat(corner + glm::vec3(0, -0.4f * length, 3), color), // 7
        VertexFormat(corner + glm::vec3(0.2f * length, -0.2f * length, 3), color), // 8
        VertexFormat(corner + glm::vec3(0.6f * length, -0.2f * length, 3), color), // 9
        VertexFormat(corner + glm::vec3(0.6f * length, 0, 3), color), // 10
        VertexFormat(corner + glm::vec3(0.6f * length, 0.2f * length, 3), color), // 9
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 0, 2, 4, 2, 3, 4, 0, 4, 5, 0, 5, 6, 0, 6, 8, 6, 7, 8, 0, 8, 1, 0, 8, 9, 0, 9, 10, 0, 10, 11, 0, 11, 2};

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateStar(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
      VertexFormat(corner, color), // 0
       VertexFormat(corner + glm::vec3(0, 0.35f * length, 1), color), // 1
        VertexFormat(corner + glm::vec3(-0.15f * length, 0.15f * length, 1), color), // 2
        VertexFormat(corner + glm::vec3(-0.35f * length, 0, 1), color), // 3
        VertexFormat(corner + glm::vec3(-0.15f * length, -0.15f * length, 1), color), // 4
        VertexFormat(corner + glm::vec3(-0.15f * length, -0.35f * length, 1), color), // 5
        VertexFormat(corner + glm::vec3(0.15f * length, -0.35f * length, 1), color), // 6
        VertexFormat(corner + glm::vec3(0.15f * length, -0.15f * length, 1), color), // 7
        VertexFormat(corner + glm::vec3(0.35f * length, 0, 1), color), // 8
        VertexFormat(corner + glm::vec3(0.15f * length, 0.15f * length, 1), color) //9
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 9, 2, 0, 2, 4, 0, 4, 7, 0, 7, 9, 9, 1, 2, 2, 3, 4, 4, 5, 7, 6, 7, 4, 7, 8, 9};

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateHeart(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
         VertexFormat(corner, color), // 0
       VertexFormat(corner + glm::vec3(0, 0.75f * length, 1), color), // 1
        VertexFormat(corner + glm::vec3(-1.5f * length, 1.5f * length, 1), color), // 2
        VertexFormat(corner + glm::vec3(-1.5f * length, 0, 1), color), // 3
        VertexFormat(corner + glm::vec3(0, -1.5f * length, 1), color), // 4
       VertexFormat(corner + glm::vec3(1.5f * length, 0, 1), color),  // 5
        VertexFormat(corner + glm::vec3(1.5f * length, 1.5f * length, 1), color), // 6
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 0, 2, 3, 0, 3, 4, 0, 4, 5, 0, 5, 6, 0, 6, 1};

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}


// gri = (0.6f, 0.6f, 0.6f)
// verde = (0.23f, 0.89f, 0.42f)
// gri inchis = (0.2f, 0.2f, 0.2f)
// rosu = (0.8f, 0.01f, 0.01f)
// portocaliu = (0.99f, 0.37f, 0.01f)
// albastru = (0.01f, 0.38f, 0.99f)
// turcoaz = (0.2f, 0.66f, 0.64f)
// galben = (0.99f, 0.83f, 0.01f)
// roz = (1, 0, 0,92f)
// mov = (0.66f, 0.01f, 0.99f)

// gri = (0.6f, 0.6f, 0.6f)
// verde = (0.2f, 0.9f, 0.4f)
// gri inchis = (0.2f, 0.2f, 0.2f)
// rosu = (0.8f, 0, 0)
// portocaliu = (1, 0.3f, 0)
// albastru = (0, 0.3f, 1)
// turcoaz = (0.2f, 0.6f, 0.6f)
// galben = (1, 0.8, 0)
// roz = (1, 0, 1)
// mov = (0.6f, 0, 1)

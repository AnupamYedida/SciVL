/*-------------shape_functions.cpp--------------------------------------------//
*
* Purpose: To keep all the functions for drawing different shapes for SciVL
*
*-----------------------------------------------------------------------------*/

#include <shape_functions.h>
#include <operations.h>
#include <ctime>

// Function to move a single vertex
void move_vertex(Shape &sh, glm::vec3 &translate, int ind){
    sh.vertices[ind*6] += translate[0];
    sh.vertices[ind*6+1] += translate[1];
    sh.vertices[ind*6+1] += translate[2];

    // Binding the vertex array object
    glBindVertexArray(sh.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, sh.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * sh.vnum*6, sh.vertices, 
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sh.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint) * sh.ind, 
                 sh.indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(GLfloat),
                          (GLvoid*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

}

// Function to move shape
void move_shape(Shape &sh, glm::vec3 &translate){
    for (int i = 0; i < sh.vnum; ++i){
         sh.vertices[i * 6 + 0] += translate[0];
         sh.vertices[i * 6 + 1] += translate[1];
         sh.vertices[i * 6 + 2] += translate[2];
    }

    // Binding the vertex array object
    glBindVertexArray(sh.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, sh.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * sh.vnum*6, sh.vertices, 
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sh.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint) * sh.ind, 
                 sh.indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(GLfloat),
                          (GLvoid*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

}


// Function to transform shape
void transform_shape(Shape &sh, glm::mat3 &transform){
}


// Function to draw a single shape
void draw_shape(Param &par, Shape &sh){

    par.shmap["default"].Use();
    glBindVertexArray(sh.VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sh.EBO);
    glDrawElements(sh.rtype, sh.ind, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

// Function to draw all shapes in the par shape map
void draw_shapes(Param &par){
    if (par.shapes.size() > 0){
        for (auto &sh : par.shapes){
            draw_shape(par, sh);
        }
    }

}

void create_rectangle(Shape &rect, glm::vec3 &pos, 
                      glm::vec3 &dim, glm::vec3 &color){

    rect.vertices = (GLfloat*)malloc(sizeof(GLfloat)*24);
    rect.vertices[0] = -dim[0] * 0.5f + pos[0];
    rect.vertices[1] = -dim[1] * 0.5f + pos[1];
    rect.vertices[2] = 0.0f;
    rect.vertices[3] = color[0];
    rect.vertices[4] = color[1];
    rect.vertices[5] = color[2];
    rect.vertices[6] = -dim[0] * 0.5f + pos[0];
    rect.vertices[7] = dim[1] * 0.5f + pos[1];
    rect.vertices[8] = 0.0f;
    rect.vertices[9] = color[0];
    rect.vertices[10] = color[1];
    rect.vertices[11] = color[2];
    rect.vertices[12] = dim[0] * 0.5f + pos[0];
    rect.vertices[13] = dim[1] * 0.5f + pos[1];
    rect.vertices[14] = 0.0f;
    rect.vertices[15] = color[0];
    rect.vertices[16] = color[1];
    rect.vertices[17] = color[2];
    rect.vertices[18] = dim[0] * 0.5f + pos[0];
    rect.vertices[19] = -dim[1] * 0.5f + pos[1];
    rect.vertices[20] = 0.0f;
    rect.vertices[21] = color[0];
    rect.vertices[22] = color[1];
    rect.vertices[23] = color[2];

    rect.indices = (GLuint*)malloc(sizeof(GLuint) * 6);
    rect.indices[0] = 0;
    rect.indices[1] = 1;
    rect.indices[2] = 3;
    rect.indices[3] = 2;
    rect.indices[4] = 1;
    rect.indices[5] = 3;

    GLuint VAO, VBO, EBO;

    // Generating objects
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Binding the vertex array object
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 24, rect.vertices, 
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint) * 6, 
                 rect.indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(GLfloat),
                          (GLvoid*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Setting square attributes
    rect.VAO = VAO;
    rect.VBO = VBO;
    rect.EBO = EBO;

    rect.vnum = 4;
    rect.ind = 6;

}

// Function to create a square shape centered at the origin of length 1
Shape create_square(Param &par){
    Shape square;

    GLfloat rad = 0.5f;
    if (par.dmap.find("radius") != par.dmap.end()){
        rad = (GLfloat)par.dmap["radius"];
    }

    GLfloat vertices[] = {
        -rad, -rad, 0.0f, 1.0f, 0.0f, 1.0f,
        -rad, rad, 0.0f, 1.0f, 0.0f, 1.0f,
        rad, rad, 0.0f, 1.0f, 0.0f, 1.0f,
        rad, -rad, 0.0f, 1.0f, 0.0f, 1.0f
    };
    square.vertices = (GLfloat*)malloc(sizeof(vertices)*24);
    for (int i = 0; i < 24; ++i){
        square.vertices[i] = vertices[i];
    }

    square.indices = (GLuint*)malloc(sizeof(GLuint) * 6);
    square.indices[0] = 0;
    square.indices[1] = 1;
    square.indices[2] = 3;
    square.indices[3] = 2;
    square.indices[4] = 1;
    square.indices[5] = 3;


    GLuint VAO, VBO, EBO;

    // Generating objects
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Binding the vertex aray object
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 24, square.vertices, 
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint) * 6, 
                 square.indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(GLfloat),
                          (GLvoid*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Setting square attributes
    square.VAO = VAO;
    square.VBO = VBO;
    square.EBO = EBO;

    square.vnum = 4;
    square.ind = 6;

    return square;
}


// function to draw a circle, must have a radius and position
void draw_circle(Param &par){

    // Pull appropriate variables from parameter list
    double radius = par.dmap["radius"];
    double pos_x = par.dmap["pos_x"];
    double pos_y = par.dmap["pos_y"];

    int res = par.imap["res"];

    // Using immediate mode, drawing a circle is easy using parametric eqns

    glBegin(GL_POLYGON);
    double theta = 0;
    for (int i = 0; i < res; i++){
        theta = -M_PI + 2*M_PI*i/(res-1);
        glVertex2f(pos_x + radius * cos(theta), pos_y + radius * sin(theta));
    }

    glEnd();
    
}

// Function to create a circle for drawing
void create_circle(Shape &circle, glm::vec3 &pos, double radius, 
                   glm::vec3 color, int res){

    circle.vertices = (GLfloat*)malloc(sizeof(GLfloat) * 6 * (res+1));

    // Allocating all the vertices
    int index = 0;
    float angle = 0;
    glm::vec3 offset;
    for (int i = 0; i < res+1; ++i){
        // Now to assign the positions
        if (i == 0){
            circle.vertices[index] = pos[0];
            circle.vertices[index+1] = pos[1];
            circle.vertices[index+2] = pos[2];
        }

        // Any point that is not the origin, note angle from 0->2pi
        else{
            angle = (i-1) * 2.0f * M_PI / res;
            offset[0] = cos(angle) * radius;
            offset[1] = sin(angle) * radius;
            offset[2] = 0.0;
            circle.vertices[index] = pos[0] + offset[0];
            circle.vertices[index+1] = pos[1] + offset[1];
            circle.vertices[index+2] = pos[2] + offset[2];
        }
        // Manual assignment of color
        circle.vertices[index+3] = color[0];
        circle.vertices[index+4] = color[1];
        circle.vertices[index+5] = color[2];
        index += 6;
    }

    // Allocating all the indices
    circle.indices = (GLuint*)malloc(sizeof(GLuint) * 3 * res);

    // This might be the same as circle fan, as before
    index = 0;
    for (int i = 1; i < res+1; ++i){
        circle.indices[index] = 0;
        circle.indices[index+1] = i;
        circle.indices[index+2] = i+1;
        index += 3;
    }

    // Setting last element to first element to complete circle
    circle.indices[res*3 - 1] = 1;

    GLuint VAO, VBO, EBO;

    // Generating objects
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Binding the vertex array object
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6*(res+1), circle.vertices, 
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint) * res * 3, 
                 circle.indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(GLfloat),
                          (GLvoid*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Setting square attributes
    circle.VAO = VAO;
    circle.VBO = VBO;
    circle.EBO = EBO;

    circle.vnum = res+1;
    circle.ind = res*3;
    std::cout << "index number is: " << circle.ind << '\n';

}

// Function to animate the drawing of a circle
void grow_circle(Shape &circle, glm::vec3 &pos, double radius, 
                 glm::vec3 color, double draw_time){

    // This will be split up into a growing phase and a shrinking phase
    
/*
    if (((std::clock() - circle.time) / (double) CLOCKS_PER_SECOND) 
        < draw_time * 0.75){
    }
    else{
    }
*/
    

}

// Function to animate the drawing of a line
void animate_line(Shape &line, std::vector<glm::vec3> &array, glm::vec3 color,
                  double start_time, double end_time){


}

// Function to set up text quads
void create_quad(Shape &quad){

    glGenVertexArrays(1, &quad.VAO);
    glGenBuffers(1, &quad.VBO);
    glBindVertexArray(quad.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, quad.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, 
                 GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

// Function to update an array
void update_line(Shape &sh, glm::vec3 *new_array){

    int size = sh.vnum / 4;
    for (int i = 0; i < size; ++i){

        sh.vertices[0+i*24]  = new_array[i].x - sh.rad;
        sh.vertices[1+i*24]  = new_array[i].y - sh.rad;
        sh.vertices[2+i*24]  = new_array[i].z;

        sh.vertices[6+i*24]  = new_array[i].x - sh.rad;
        sh.vertices[7+i*24]  = new_array[i].y + sh.rad;
        sh.vertices[8+i*24]  = new_array[i].z;

        sh.vertices[12+i*24] = new_array[i].x + sh.rad;
        sh.vertices[13+i*24] = new_array[i].y - sh.rad;
        sh.vertices[14+i*24] = new_array[i].z;

        sh.vertices[18+i*24] = new_array[i].x + sh.rad;
        sh.vertices[19+i*24] = new_array[i].y + sh.rad;
        sh.vertices[20+i*24] = new_array[i].z;
    }

    // Resetting the indices.
    double slope;
    for (int i = 0; i < size-1; ++i){
        slope = (new_array[i].y - new_array[i+1].y) 
                / (new_array[i].x - new_array[i+1].x);
        if (slope >= 0){
            sh.indices[6+i*12] = 4*i+2;
            sh.indices[7+i*12] = 4*i+1;
            sh.indices[8+i*12] = 4*i+5;
            sh.indices[9+i*12] = 4*i+2;
            sh.indices[10+i*12] = 4*i+6;
            sh.indices[11+i*12] = 4*i+5;
        }
        else{
            sh.indices[6+i*12] = 4*i+3;
            sh.indices[7+i*12] = 4*i+7;
            sh.indices[8+i*12] = 4*i+4;
            sh.indices[9+i*12] = 4*i+3;
            sh.indices[10+i*12] = 4*i;
            sh.indices[11+i*12] = 4*i+4;
        }

        sh.indices[12+i*12] = 4*i+4;
        sh.indices[13+i*12] = 4*i+5;
        sh.indices[14+i*12] = 4*i+7;
        sh.indices[15+i*12] = 4*i+4;
        sh.indices[16+i*12] = 4*i+6;
        sh.indices[17+i*12] = 4*i+7;
    }


    GLuint VAO, VBO, EBO;

    // Generating objects
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Binding the vertex array object
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * sh.vnum * 24,
                 sh.vertices, GL_STATIC_DRAW);

    // Setting the indices again.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint) * ((size-1) * 12 + 6), 
                 sh.indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(GLfloat),
                          (GLvoid*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Setting square attributes
    sh.VAO = VAO;
    sh.VBO = VBO;
    sh.EBO = EBO;

}

// function to create array shape
void create_line(Shape &line, std::vector<glm::vec3> &array, glm::vec3 &color){
    create_line(line, array.data(), array.size(), color);
}
void create_line(Shape &line, glm::vec3 *array, int size, glm::vec3 &color){

    // Setting render type to GL_LINES
    //line.rtype = GL_POINTS | GL_LINES;
    line.rtype = GL_TRIANGLES;

    // Allocating space for vertices -- 2 points for every vertex!
    line.vertices = (GLfloat*)malloc(sizeof(GLfloat)*24*size);
    double slope;

    // This is done in a 3 step process
    //     1. Find slope of points before and after our element
    //     2. Find a slope perpendicular to the slope found in 1
    //     3. Extend that slope in both directions based on the radius
    for (int i = 0; i < size; ++i){
        // Special cases for our first and last elements
        line.vertices[0+i*24]  = array[i].x - line.rad;
        line.vertices[1+i*24]  = array[i].y - line.rad;
        line.vertices[2+i*24]  = array[i].z;
        line.vertices[3+i*24]  = color[0];
        line.vertices[4+i*24]  = color[1];
        line.vertices[5+i*24]  = color[2];

        line.vertices[6+i*24]  = array[i].x - line.rad;
        line.vertices[7+i*24]  = array[i].y + line.rad;
        line.vertices[8+i*24]  = array[i].z;
        line.vertices[9+i*24]  = color[0];
        line.vertices[10+i*24] = color[1];
        line.vertices[11+i*24] = color[2];

        line.vertices[12+i*24] = array[i].x + line.rad;
        line.vertices[13+i*24] = array[i].y - line.rad;
        line.vertices[14+i*24] = array[i].z;
        line.vertices[15+i*24] = color[0];
        line.vertices[16+i*24] = color[1];
        line.vertices[17+i*24] = color[2];

        line.vertices[18+i*24] = array[i].x + line.rad;
        line.vertices[19+i*24] = array[i].y + line.rad;
        line.vertices[20+i*24] = array[i].z;
        line.vertices[21+i*24] = color[0];
        line.vertices[22+i*24] = color[1];
        line.vertices[23+i*24] = color[2];

    }

    // Allocating space for indices
    // FIX
    line.indices = (GLuint*)malloc(sizeof(GLuint)*((size-1)*12 + 6));

    // Setting up initial triangle
    line.indices[0] = 0;
    line.indices[1] = 1;
    line.indices[2] = 2;
    line.indices[3] = 1;
    line.indices[4] = 2;
    line.indices[5] = 3;

    for (int i = 0; i < size-1; ++i){
        slope = (array[i].y - array[i+1].y) / (array[i].x - array[i+1].x);
        if (slope >= 0){
            line.indices[6+i*12] = 4*i+2;
            line.indices[7+i*12] = 4*i+1;
            line.indices[8+i*12] = 4*i+5;
            line.indices[9+i*12] = 4*i+2;
            line.indices[10+i*12] = 4*i+6;
            line.indices[11+i*12] = 4*i+5;
        }
        else{
            line.indices[6+i*12] = 4*i+3;
            line.indices[7+i*12] = 4*i+7;
            line.indices[8+i*12] = 4*i+4;
            line.indices[9+i*12] = 4*i+3;
            line.indices[10+i*12] = 4*i;
            line.indices[11+i*12] = 4*i+4;
        }

        line.indices[12+i*12] = 4*i+4;
        line.indices[13+i*12] = 4*i+5;
        line.indices[14+i*12] = 4*i+7;
        line.indices[15+i*12] = 4*i+4;
        line.indices[16+i*12] = 4*i+6;
        line.indices[17+i*12] = 4*i+7;
    }


    GLuint VAO, VBO, EBO;

    // Generating objects
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Binding the vertex array object
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * size * 24,
                 line.vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint) * ((size-1) * 12 + 6), 
                 line.indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(GLfloat),
                          (GLvoid*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Setting square attributes
    line.VAO = VAO;
    line.VBO = VBO;
    line.EBO = EBO;

    line.vnum = size*4;
    line.ind = (size-1)*12 +6;
}

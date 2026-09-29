#include"VAO.h"

// Constructor that generates a VAO ID
VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

// Links a VBO to the VAO using a certain layout
void VAO::LinkVBO(VBO& VBO, GLuint layout)
{
	VBO.Bind();

	if (layout == 0) {
		// posición: 3 floats, empieza en el byte 0
		glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	}
	else if (layout == 1) {
		// UV: 2 floats, empieza después de los 3 floats de posición
		glVertexAttribPointer(layout, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	}

	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

// Binds the VAO
void VAO::Bind()
{
	glBindVertexArray(ID);
}

// Unbinds the VAO
void VAO::Unbind()
{
	glBindVertexArray(0);
}

// Deletes the VAO
void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}
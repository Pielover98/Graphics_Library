#include "graphics\RenderObjects.h"
#include "graphics\draw.h"
#include "graphics/glinc.h"
#include "glm\glm.hpp"
#include <glm/gtc/type_ptr.hpp>

void s0_draw(const Framebuffer &f, const Shader &s, const Geometry &g)
{
	//what are we using
	glBindFramebuffer(GL_FRAMEBUFFER, f.handle);
	glUseProgram(s.handle);
	glBindVertexArray(g.handle);

	//what area of the framebuffer do we draw to
	glViewport(0, 0, f.width, f.height);

	//draw it 
	glDrawElements(GL_TRIANGLES, g.size, GL_UNSIGNED_INT, 0);

	// unbind if you want
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glUseProgram(0);
	glBindVertexArray(0);
}

void tf0_update(const Shader & s, const ParticleBuffer & pb, int active)
{
	glBeginTransformFeedback(GL_POINTS);

	glBindTexture(GL_TEXTURE_3D, s.handle);

	glDrawArrays(GL_POINTS, 0, 1000);

	glEndTransformFeedback();


	// Swap the A and B buffers for ping-ponging, then turn the rasterizer back on:

	//std::swap(pb.handle[0], pb.handle[1]);

	glDisable(GL_RASTERIZER_DISCARD);

}

void tf0_draw(const Framebuffer & s, const Shader & sp, const ParticleBuffer & pb)
{
	glUseProgram(s.handle);

	glBindBuffer(GL_ARRAY_BUFFER, pb.handle[0]);

	glVertexAttribPointer(sp.handle, 3, GL_FLOAT, GL_FALSE, 16, pb.vbo);

	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 16, 12 + pb.vbo);

	glDrawArrays(GL_POINTS, 0, 1000);

}

void setUniform(const Shader & s, int location, float value)
{
	glProgramUniform1f(s.handle, location, value);

}

void setUniform(const Shader & s, int location, int value)
{
	glProgramUniform1i(s.handle, location, value);

}

void setUniform(const Shader & s, int location, const Texture & value, unsigned slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, value.handle);

	glProgramUniform1i(s.handle, location, slot);
}


void setFlags(int flags)
{
	//depth testing

	if (flags & RenderFlag::DEPTH)
	{
		glEnable(GL_DEPTH_TEST);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
	}

	if (flags &RenderFlag::ADDITIVE)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
	}
	else
	{
		glDisable(GL_BLEND);
	}
}
void clearFramebuffer(const Framebuffer & r, bool color, bool depth)
{
	glBindFramebuffer(GL_FRAMEBUFFER, r.handle);
	glClear(GL_COLOR_BUFFER_BIT * color | GL_DEPTH_BUFFER_BIT * depth);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

namespace _internal
{
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, float val)
	{
		glProgramUniform1f(s.handle, loc_io++, val);
	}
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, int val)
	{
		glProgramUniform1i(s.handle, loc_io++, val);
	}
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const Texture &val)
	{
		glActiveTexture(GL_TEXTURE0 + tex_io);
		glBindTexture(GL_TEXTURE_2D, val.handle);
		glProgramUniform1i(s.handle, loc_io++, tex_io++);
	}
	void t_setUniform(const Shader & s, int & loc_io, int & tex_io, const Skybox & val)
	{
		glActiveTexture(GL_TEXTURE0 + tex_io);
		glBindTexture(GL_TEXTURE_CUBE_MAP, val.handle);
		glProgramUniform1i(s.handle, loc_io++, tex_io++);
	}
	void t_setUniform(const Shader & s, int &location, int &tex_io, const glm::vec4 &value)
	{
		glProgramUniform4fv(s.handle, location++, 1, glm::value_ptr(value));
	}
	void t_setUniform(const Shader & s, int &location, int &tex_io, const glm::vec2 &value)
	{
		glProgramUniform2fv(s.handle, location++, 1, glm::value_ptr(value));
	}
	void t_setUniform(const Shader & s, int &location, int &tex_io, const glm::vec3 &value)
	{
		glProgramUniform3fv(s.handle, location++, 1, glm::value_ptr(value));
	}
	void t_setUniform(const Shader & s, int &location, int &tex_io, const glm::mat4 &value)
	{
		glProgramUniformMatrix4fv(s.handle, location++, 1, 0, glm::value_ptr(value));
	}
}

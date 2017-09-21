﻿#include "graphics\RenderObjects.h"
#include "graphics\GameObjects.h"
#include "graphics\draw.h"
#include "graphics\glinc.h"
#include <utility>

void setFlags(int flags)
{

	if (flags & RenderFlag::DEPTH)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);

	if (flags &RenderFlag::ADDITIVE) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
	}

	else glDisable(GL_BLEND);
}

void s0_draw(const Framebuffer & f, const Shader & s, const Geometry & g)
{

	glBindFramebuffer(GL_FRAMEBUFFER, f.handle);
	glUseProgram(s.handle);
	glBindVertexArray(g.handle);


	glViewport(0, 0, f.width, f.height);


	glDrawElements(GL_TRIANGLES, g.size, GL_UNSIGNED_INT, 0);
}


void tf0_update(const Shader & s, const ParticleBuffer & pb, int active)
{
	static const char* varyings[] = { "outPos","outVel","outCol" };

	glTransformFeedbackVaryings(s.handle, 3, varyings, GL_INTERLEAVED_ATTRIBS);



	glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, pb.handle[active]);
	glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, pb.size, NULL, GL_DYNAMIC_COPY);

	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, pb.vbo[active]);

}

void tf0_draw(const Framebuffer & f, const Shader & s, const ParticleBuffer & pb)
{


	glEnable(GL_RASTERIZER_DISCARD);

	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, pb.vbo[0]);

	glBeginTransformFeedback(GL_TRIANGLES);

	glDrawElements(GL_TRIANGLES, pb.size, GL_UNSIGNED_INT, 0);

	glEndTransformFeedback();
}

void clearFramebuffer(const Framebuffer & fb, bool color, bool depth)
{
	glBindFramebuffer(GL_FRAMEBUFFER, fb.handle);
	glClear(GL_COLOR_BUFFER_BIT * color | GL_DEPTH_BUFFER_BIT * depth);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void setUniform(const Shader &s, int location, float value)
{
	glProgramUniform1f(s.handle, location, value);
}

void setUniform(const Shader & s, int location, int value)
{

	if (value == 1) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
	}
	else {
		glProgramUniform1i(s.handle, location, value);
		glDisable(GL_BLEND);
	}
}

void setUniform(const Shader & s, int location, const Texture & value, unsigned slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, value.handle);

	glProgramUniform1i(s.handle, location, slot);
}

namespace __internal
{
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, float val) {
		glProgramUniform1f(s.handle, loc_io++, val);
	}
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, int val) {
		glProgramUniform1i(s.handle, loc_io++, val);
	}
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const Texture &val) {
		glActiveTexture(GL_TEXTURE0 + tex_io);
		glBindTexture(GL_TEXTURE_2D, val.handle);
		glProgramUniform1i(s.handle, loc_io++, tex_io++);
	}
	void t_setUniform(const Shader & s, int & loc_io, int & tex_io, const CubeTexture & val)
	{
		glActiveTexture(GL_TEXTURE0 + tex_io);
		glBindTexture(GL_TEXTURE_CUBE_MAP, val.handle);
		glProgramUniform1i(s.handle, loc_io++, tex_io++);
	}

	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const glm::mat4 &val) {
		glProgramUniformMatrix4fv(s.handle, loc_io++, 1, 0, glm::value_ptr(val));
	}
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const glm::vec4 &val) {
		glProgramUniform4fv(s.handle, loc_io++, 1, glm::value_ptr(val));
	}
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const glm::vec3 &val) {
		glProgramUniform3fv(s.handle, loc_io++, 1, glm::value_ptr(val));

	}
}
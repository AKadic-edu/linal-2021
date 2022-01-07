#include "assessment.hpp"

#include <mathlib/matrix.hpp>
#include <mathlib/vector.hpp>
#include <mathlib/utils/operations.hpp>
#include <mathlib/utils/transforms.hpp>
#include <videolib/instance.hpp>
#include <videolib/key.hpp>
#include <videolib/renderer.hpp>
#include <videolib/window.hpp>

#include "src/camera.hpp"
#include "src/resources.hpp"
#include "src/spaceship.hpp"

float quadSize = 0.1f;
float minSize =  1.0f;
float maxSize = 2.0f;
float animationSpeed = 0.00002f;

bool debug = false;

ml::Vector<float, 2> clip(const ml::Vector<float, 2>& v)
{
	auto out = v;

	if (out[0] < -1.0f) out[0] = -1.0f;
	if (out[1] < -1.0f) out[1] = -1.0f;
	if (out[0] >  1.0f) out[0] =  1.0f;
	if (out[1] >  1.0f) out[1] =  1.0f;

	return out;
}

float rotation = 0.0f;
float bulletScale = 0.5f;
float xMax = 50.0f;
float yMax = 50.0f;
float zMax = 50.0f;

ml::Vector<float, 3> position { 0.0f, 0.0f , 3.0f };
ml::Vector<float, 3> front { 0.0f, 0.0f , -1.0f };
ml::Vector<float, 3> up { 0.0f, 1.0f , 0.0f };

float yaw = -90.0f;
float pitch = 0.0f;
float fov = 90.0f;

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

bool outOfBounds(ml::Vector<float, 3> pos)
{
	return pos[0] > xMax || pos[0] < -xMax
		|| pos[1] > yMax || pos[1] < -yMax
		|| pos[2] > zMax || pos[2] < -zMax;
}

//Model animate(Model m)
//{
//	//if (m.modelM[0][0] < minSize || m.modelM[0][0] > maxSize) {
//	//	animationSpeed = -animationSpeed;
//	//}
//
//	//m.modelM[0][0] += animationSpeed;
//	//m.modelM[1][1] += animationSpeed;
//	//m.modelM[2][2] += animationSpeed;
//
//	return m;
//}

int main(int argc, char* args[])
{
	vl::Window window { "LINAL Assessment", 640, 480 };
	vl::Instance instance { window };

	Spaceship spaceship;

	ml::Vector<float, 3> front { 0.0f, 0.0f, -1.0f };

	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;

	float rotationSpeed = 2.0f;

	float lastX = window.width / 2.0f;
	float lastY = window.height / 2.0f;

	instance.onKeyDown([&](vl::Key k) {
		if (k == vl::Key::spacebar) {
			spaceship.fire();
		}
		if (k == vl::Key::h) {
			debug = !debug;
		}

		if (k == vl::Key::escape) instance.stop();

		if (k == vl::Key::q) spaceship.steer({  rotationSpeed, 0.0f, 0.0f });
		if (k == vl::Key::e) spaceship.steer({ -rotationSpeed, 0.0f, 0.0f });
		if (k == vl::Key::w) spaceship.steer({ 0.0f,  rotationSpeed, 0.0f });
		if (k == vl::Key::s) spaceship.steer({ 0.0f, -rotationSpeed, 0.0f });
		if (k == vl::Key::a) spaceship.steer({ 0.0f, 0.0f,  rotationSpeed });
		if (k == vl::Key::d) spaceship.steer({ 0.0f, 0.0f, -rotationSpeed });

		if (k == vl::Key::up) position += front;
		if (k == vl::Key::down) position -= front;
		if (k == vl::Key::left) position -= ml::normalize(ml::cross(front, up));
		if (k == vl::Key::right) position += ml::normalize(ml::cross(front, up));
	});

	bool firstMouse = true;

	instance.onMouseMove([&](float x, float y) {
		if (firstMouse)
		{
			lastX = x;
			lastY = y;
			firstMouse = false;
		}

		float xoffset = x - lastX;
		float yoffset = y - lastY;
		lastX = x;
		lastY = y;

		const float sensitivity = 100.0f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		ml::Vector<float, 3> f {
			std::cos(ml::radians(yaw)) * std::cos(ml::radians(pitch)),
			std::sin(ml::radians(pitch)),
			std::sin(ml::radians(yaw)) * std::cos(ml::radians(pitch))
		};

		front = ml::normalize(f);
	});

	instance.onMouseScroll([&](float x, float y) {
		int zoom = (int)std::ceil(y);

		fov += zoom;
	});

	float basis = 1.0f;
	float bulletSpeed = 0.5f;

	float t = 0.0f;

	return instance.run([&](vl::Renderer& r, float dt) {
		r.debug(debug);
		deltaTime = dt;

		const float radius = 10.0f;

		float aspect = (float)window.width / window.height;
		Camera<3> cam;
		cam.position = position;
		cam.target = cam.position + front;
		cam.up = up;
		const auto projectionM = perspective(cam, 100.0f, 0.1f, fov);
		const auto viewM = view(cam);
		auto vp = projectionM * viewM;

		r.clear(255, 255, 255);

		if (debug) {
			r.color(255, 0, 0);
			r.drawVector(vp, { aspect * basis, 0.0f, 0.0f });
			r.color(0, 255, 0);
			r.drawVector(vp, { 0.0f, aspect * basis, 0.0f });
			r.color(0, 0, 255);
			r.drawVector(vp, { 0.0f, 0.0f, aspect * basis });
		}

		spaceship.update(dt);
		spaceship.draw(r, vp);
	});
}

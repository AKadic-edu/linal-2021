#include "assessment.hpp"

#include <mathlib/matrix.hpp>
#include <mathlib/vector.hpp>
#include <mathlib/utils/operations.hpp>
#include <mathlib/utils/transforms.hpp>
#include <videolib/instance.hpp>
#include <videolib/renderer.hpp>
#include <videolib/window.hpp>
#include <videolib/shapes/line.hpp>

#include "src/camera.hpp"
#include "src/resources.hpp"
#include "src/view.hpp"

float quadSize = 0.1f;
float minSize =  1.0f;
float maxSize = 2.0f;
float animationSpeed = 0.00002f;

bool showAxis = false;

struct Model {
	ml::Matrix<float, 4, 4> worldM { ml::identity<float, 4, 4>() };
	ml::Matrix<float, 4, 4> modelM { ml::identity<float, 4, 4>() };
	std::vector<ml::Vector<float, 3>> vertices;
};

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

Model generateBullet(ml::Matrix<float, 4, 4> w, ml::Matrix<float, 4, 4> m)
{
	Model bullet;

	for (int i = 0; i < sizeof(cubeVertices) / sizeof(*cubeVertices); i += 3) {
		bullet.vertices.push_back({ cubeVertices[i], cubeVertices[i + 1], cubeVertices[i + 2] });
	}

	bullet.modelM = m;
	bullet.worldM = w;

	return bullet;
}

Model animate(Model m)
{
	//if (m.modelM[0][0] < minSize || m.modelM[0][0] > maxSize) {
	//	animationSpeed = -animationSpeed;
	//}

	//m.modelM[0][0] += animationSpeed;
	//m.modelM[1][1] += animationSpeed;
	//m.modelM[2][2] += animationSpeed;

	return m;
}

void drawVector(vl::Renderer& r, ml::Matrix<float, 4, 4> vp, ml::Vector<float, 3> basis)
{
	const auto aTransformed = vp * ml::Vector<float, 4> {  basis[0],  basis[1],  basis[2], 1.0f };
	const auto bTransformed = vp * ml::Vector<float, 4> { 0.0f, 0.0f, 0.0f, 1.0f };

	if (aTransformed[3] < 0 || bTransformed[3] < 0) return;

	const ml::Vector<float, 2> aClipped{ aTransformed[0] / aTransformed[3], aTransformed[1] / aTransformed[3] };
	const ml::Vector<float, 2> bClipped{ bTransformed[0] / bTransformed[3], bTransformed[1] / bTransformed[3] };

	r.drawLine({ aClipped[0], aClipped[1], bClipped[0], bClipped[1] });
}

void drawModel(vl::Renderer& r, ml::Matrix<float, 4, 4> vp, Model m)
{
	std::vector<vl::Line> lines;

	for (int i = 0; i < m.vertices.size(); ++i) {
		const auto& a = m.vertices[i];
		const auto& b = m.vertices[(i + 1) % m.vertices.size()];

		const auto aTransformed = vp * m.worldM * m.modelM * ml::Vector<float, 4> { a[0], a[1], a[2], 1.0f };
		const auto bTransformed = vp * m.worldM * m.modelM * ml::Vector<float, 4> { b[0], b[1], b[2], 1.0f };

		if (aTransformed[3] < 0 || bTransformed[3] < 0) break;

		const ml::Vector<float, 2> aClipped { aTransformed[0] / aTransformed[3], aTransformed[1] / aTransformed[3] };
		const ml::Vector<float, 2> bClipped { bTransformed[0] / bTransformed[3], bTransformed[1] / bTransformed[3] };

		lines.push_back({ aClipped[0], aClipped[1], bClipped[0], bClipped[1] });
	}
	r.drawLines(lines);

	if (showAxis) {
		r.color(255, 0, 0);
		drawVector(r, vp * m.worldM, { 1.0f, 0.0f, 0.0f });
		r.color(0, 255, 0);
		drawVector(r, vp * m.worldM, { 0.0f, 1.0f, 0.0f });
		r.color(0, 0, 255);
		drawVector(r, vp * m.worldM, { 0.0f, 0.0f, 1.0f });
	}
}

int main(int argc, char* args[])
{
	vl::Window window { "LINAL Assessment", 640, 480 };
	vl::Instance instance { window };

	Model quad;
	for (int i = 0; i < sizeof(cubeVertices)/sizeof(*cubeVertices); i += 3) {
		quad.vertices.push_back({ cubeVertices[i], cubeVertices[i + 1], cubeVertices[i + 2] });
	}
	Model spaceship;
	for (int i = 0; i < sizeof(spaceshipVertices) / sizeof(*spaceshipVertices); i += 3) {
		spaceship.vertices.push_back({ spaceshipVertices[i], spaceshipVertices[i + 1], spaceshipVertices[i + 2] });
	}
	spaceship.modelM = spaceship.modelM * ml::rotate(0.0f, 0.0f, -90.0f) * ml::scale(1.0f, 2.0f, 1.0f) * ml::scale(0.5f);

	ml::Vector<float, 3> front { 0.0f, 0.0f, -1.0f };

	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;

	float rotationSpeed = 2.0f;

	std::vector<Model> bullets;

	float lastX = window.width / 2.0f;
	float lastY = window.height / 2.0f;

	instance.onKeyDown([&](vl::Key k) {
		if (k == vl::Key::lctrl) {
			spaceship.worldM[3] = spaceship.worldM[3] + spaceship.modelM[2];
		}
		if (k == vl::Key::spacebar) {
			bullets.push_back(generateBullet(quad.worldM, quad.modelM));
		}
		if (k == vl::Key::h) {
			showAxis = !showAxis;
		}

		if (k == vl::Key::escape) instance.stop();

		if (k == vl::Key::q) quad.modelM = ml::rotate(0.0f, 0.0f, rotationSpeed) * quad.modelM;
		if (k == vl::Key::e) quad.modelM = ml::rotate(0.0f, 0.0f, -rotationSpeed) * quad.modelM;

		if (k == vl::Key::w) position += front;
		if (k == vl::Key::s) position -= front;
		if (k == vl::Key::a) position -= ml::normalize(ml::cross(front, up));
		if (k == vl::Key::d) position += ml::normalize(ml::cross(front, up));
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
			std::cos(ml::radians(yaw))* std::cos(ml::radians(pitch)),
			std::sin(ml::radians(pitch)),
			std::sin(ml::radians(yaw))* std::cos(ml::radians(pitch))
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
		deltaTime = dt;

		auto it = bullets.begin();
		while (it != bullets.end()) {
			auto& b = (*it);

			b.worldM[3] = b.worldM[3] + (bulletSpeed * (b.modelM[2]));

			if (outOfBounds({ b.worldM[3][0], b.worldM[3][1], b.worldM[3][2] })) {
				it = bullets.erase(it);
			}
			else ++it;
		}

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

		if (showAxis) {
			r.color(255, 0, 0);
			drawVector(r, vp, { aspect * basis, 0.0f, 0.0f });
			r.color(0, 255, 0);
			drawVector(r, vp, { 0.0f, aspect * basis, 0.0f });
			r.color(0, 0, 255);
			drawVector(r, vp, { 0.0f, 0.0f, aspect * basis });
		}

		r.color(0, 0, 0);
		drawModel(r, vp, spaceship);
	});
}

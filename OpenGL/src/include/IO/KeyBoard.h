#pragma once
struct KeyboardHandler {
	std::function<void(int key, int action)> onKeyPress;
	double lastKeyTime = 0.0;
	double keyDelay = 0.3; // 防止连续触发

	void Update(GLFWwindow* window) {
		double currentTime = glfwGetTime();
		if (currentTime - lastKeyTime < keyDelay) return;

		//常用按键检测
		for (int key = GLFW_KEY_A; key <= GLFW_KEY_Z; ++key) {
			if (glfwGetKey(window, key) == GLFW_PRESS) {
				if (onKeyPress) onKeyPress(key, GLFW_PRESS);
				lastKeyTime = currentTime;
				break;
			}
		}
		// 特殊按键
		int specialKeys[] = { GLFW_KEY_SPACE, GLFW_KEY_ENTER, GLFW_KEY_ESCAPE,
						   GLFW_KEY_UP, GLFW_KEY_DOWN, GLFW_KEY_LEFT, GLFW_KEY_RIGHT };
		for (int key : specialKeys) {
			if (glfwGetKey(window, key) == GLFW_PRESS) {
				if (onKeyPress) onKeyPress(key, GLFW_PRESS);
				lastKeyTime = currentTime;
				break;
			}
		}
	}
};

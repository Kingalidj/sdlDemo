#include <stdio.h>
#include <iostream>
#include "renderEngine.h"

#undef main

int main() {

	renderEngine window(1200, 1200);

	window.start();

	return 0;
}


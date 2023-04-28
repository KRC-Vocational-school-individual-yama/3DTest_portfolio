#pragma once

template<typename NAME>
struct Vec2 {
	NAME x, y;
};

template<typename NAME>
struct Circle {
	Vec2<NAME> pos;
	NAME radius;
};
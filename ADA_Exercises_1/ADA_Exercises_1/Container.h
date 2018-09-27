#pragma once
namespace my_containers {
	class Container
	{
	public:
		template<typename T> Container();
		~Container();

		virtual size_t size();
	};
}


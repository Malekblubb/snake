//
// Copyright (c) 2013 Christoph Malek
// See LICENSE for more information.
//

#include <snk/game.hpp>


constexpr mlk::uint height{600}, width{600};

int main()
{return snk::game{{width, height}, "Snake"}.run();}

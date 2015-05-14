// Includes:
// .hpp if it's an implementation
#include "Common/SomeHeader.hpp"

// System/STL
#include <algorithm>
#include <iostream>

// Third-party
#include <QtCore>

// Our includes
#include "Mind/Mind.hpp"

// Indentation
#define foobar(A)\
{Foo();Bar();}
#define anotherFoo(B)\
return Bar()

namespace Bar
{
	class Foo {
	public:
		Foo();
		virtual ~Foo();
	};

	switch (foo) {
		case 1:
			a += 1;
			break;
		case 2: {
			a += 2;
			break;
		}
	}

	if (isFoo) {
		bar();
	} else {
		anotherBar();
	}

	int foo()

	while (isFoo) {
		...
		goto error;
		....
error:
		...
	}
}
fooArray[] = {
	red,
	green,
	darkblue
};
fooFunction(
	barArg1,
	barArg2,
	barArg3);
struct foo { int bar() {} };
// Formatting
void func()
{
	if (isFoo(a, b))
		bar(a, b);

	if (isFoo)
		a = bar((b - c) * a, *d--);

	if (isFoo(a, b))
		bar(a, b);

	if (isFoo) {
		isFoo = false;
		cat << isFoo << endl;
	}

	if (isFoo)
		DoBar();
	if (isFoo)
		bar();
	else if (isBar())
		anotherBar();

	int var = 1;
	int *ptr = &var;
	int &ref = i;

	QList<int>::const_iterator it = list.begin();
}

namespace A
{
	namespace B
	{
		class someClass {
			void foo()
			{
				if (true)
					func();
				else
					// bla
			}
		};
	}
}

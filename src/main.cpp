/*
FILE: main.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/8/2019
*/

#define _CRT_SECURE_NO_WARNINGS // for stb

#include <stdio.h>

#include "samples/samples.h"
#include "tests/tests.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"


int main(int argc, char **argv)
{
    // Regular sampling testing
    {
        std::vector<float> samples;
        FILE* file = fopen("output/samples/_1d/regular/discrepancy.txt", "w+b");

        Samples::_1d::Regular::Regular(samples, 16);
        Tests::_1d::Numberline::MakeNumberline("output/samples/_1d/regular/regular.png", samples, 512);

        fprintf(file, "%zu samples\r\n\r\n", samples.size());

        fprintf(file, "Regular:\r\n  Discrepancy: %0f\r\n  Wrap: %0f\r\n\r\n",
            Tests::_1d::Discrepancy::CalculateDiscrepancy(samples),
            Tests::_1d::Discrepancy::CalculateDiscrepancyWrapAround(samples)
        );

        Samples::_1d::Regular::RegularCentered(samples, 16);
        Tests::_1d::Numberline::MakeNumberline("output/samples/_1d/regular/regularcentered.png", samples, 512);

        fprintf(file, "RegularCentered:\r\n  Discrepancy: %0f\r\n  Wrap: %0f\r\n\r\n",
            Tests::_1d::Discrepancy::CalculateDiscrepancy(samples),
            Tests::_1d::Discrepancy::CalculateDiscrepancyWrapAround(samples)
        );

        Samples::_1d::Regular::RegularCenteredOffset(samples, 16);
        Tests::_1d::Numberline::MakeNumberline("output/samples/_1d/regular/regularcenteredoffset.png", samples, 512);

        fprintf(file, "RegularCenteredOffset:\r\n  Discrepancy: %0f\r\n  Wrap: %0f\r\n\r\n",
            Tests::_1d::Discrepancy::CalculateDiscrepancy(samples),
            Tests::_1d::Discrepancy::CalculateDiscrepancyWrapAround(samples)
        );

        fclose(file);
    }

    // Irrational number testing
    {
        std::vector<float> samples;
        FILE* file = fopen("output/samples/_1d/irrational_numbers/discrepancy.txt", "w+b");

        Samples::_1d::IrrationalNumbers::GoldenRatio(samples, 16);
        Tests::_1d::Numberline::MakeNumberline("output/samples/_1d/irrational_numbers/golden_ratio.png", samples, 512);

        fprintf(file, "%zu samples\r\n\r\n", samples.size());

        fprintf(file, "GoldenRatio:\r\n  Discrepancy: %0f\r\n  Wrap: %0f\r\n\r\n",
            Tests::_1d::Discrepancy::CalculateDiscrepancy(samples),
            Tests::_1d::Discrepancy::CalculateDiscrepancyWrapAround(samples)
        );

        Samples::_1d::IrrationalNumbers::Pi(samples, 16);
        Tests::_1d::Numberline::MakeNumberline("output/samples/_1d/irrational_numbers/pi.png", samples, 512);

        fprintf(file, "Pi:\r\n  Discrepancy: %0f\r\n  Wrap: %0f\r\n\r\n",
            Tests::_1d::Discrepancy::CalculateDiscrepancy(samples),
            Tests::_1d::Discrepancy::CalculateDiscrepancyWrapAround(samples)
        );

        Samples::_1d::IrrationalNumbers::Sqrt2(samples, 16);
        Tests::_1d::Numberline::MakeNumberline("output/samples/_1d/irrational_numbers/sqrt2.png", samples, 512);

        fprintf(file, "Sqrt(2):\r\n  Discrepancy: %0f\r\n  Wrap: %0f\r\n\r\n",
            Tests::_1d::Discrepancy::CalculateDiscrepancy(samples),
            Tests::_1d::Discrepancy::CalculateDiscrepancyWrapAround(samples)
        );

        Samples::_1d::IrrationalNumbers::Rational<3, 16>(samples, 16);
        Tests::_1d::Numberline::MakeNumberline("output/samples/_1d/irrational_numbers/rational_3_16.png", samples, 512);

        fprintf(file, "Rational(3,16):\r\n  Discrepancy: %0f\r\n  Wrap: %0f\r\n\r\n",
            Tests::_1d::Discrepancy::CalculateDiscrepancy(samples),
            Tests::_1d::Discrepancy::CalculateDiscrepancyWrapAround(samples)
        );

        Samples::_1d::IrrationalNumbers::Rational<2, 16>(samples, 16);
        Tests::_1d::Numberline::MakeNumberline("output/samples/_1d/irrational_numbers/rational_2_16.png", samples, 512);

        fprintf(file, "Rational(2,16):\r\n  Discrepancy: %0f\r\n  Wrap: %0f\r\n\r\n",
            Tests::_1d::Discrepancy::CalculateDiscrepancy(samples),
            Tests::_1d::Discrepancy::CalculateDiscrepancyWrapAround(samples)
        );

        fclose(file);
    }

    return 0;
}

/*
TODO:

* look into how the rational sequence of 2/16 gets a torroidal discrepancy of 1.0.  That is wrong
* renamed 1d.md files to _1d.md but need to make sure you don't break links

* do documentation for irrational numbers and link to them
* todo for other irrational numbers: silver ratio, etc.

? how does testing a progressive sequence differ from non progressive?
 * show a graph of discrepancy over sample count, to see how it changes.
 * somehow need to note that it's progressive - in documenation, and also in code?
 * for now, it's not treated as progressive or noted as progressive.

* make the test above be a "conglomerate test" and put it in the tests folder w/ documentation
 * make it auto generated from information in a lua file?
 * specify the functions to call, and if they are progressive or what.
 * for irrational tests, can pass extra params as template params (like rational number etc).

* sampling: golden ratio next? it's progressive, so is a bit special in that way.
 * maybe do white noise next? white noise is also progressive
 * blue noise? mitchell's best candidate. add todos for blue noise: poisson disk, relaxation.

? open up "1d sampling" to submissions soon, and have a page about how to make submissions
 * figure out what exactly you want to do before opening it up

* look into generating header files and documentation from lua scripts called from in premake
 * maybe tests too, and have sequences specify a "json" like file (but lua?) about their properties: progressive, randomized, etc?

* golden ratio documentation:
 * golden ratio = 1.61803398875 (put formula there too x^2+1 = x i think?). also ratio of fibonacci sequence. maybe also how 1/phi = phi - 1. only thing that it's true for.
 * most irrational number and what that means for "never repeating"
 * also, limit of ratio of fibonaci numbers as you approach infinity
 * talk about conjugate and how it's not any more or less rational
 * could show how each new sample cuts the largest existing sample into two parts: the golden ratio
 * this from numberphile about how irrational the golden ratio is: https://youtu.be/sj8Sg8qnjOg
* pi documentation:
 * show repeated fraction of golden ratio vs pi.  maybe link to that video that shows it?
 * show how pi isn't as irrational.
 * show pi not performing as well at integration tests etc
* sqrt2 documentation:
 * discrepancy bad in low sample counts but gets better?





* add to blue noise notes... blue noise from eigenvectors
 * https://twitter.com/TechSparx/status/1093902404867760129

* make numberlines have a bool to have nodes be a color based on index? to show progressive sequences.
 * maybe always want it on? not sure.



Documentation WIP:

Guidelines overall:
* Code should be copy / paste-able
* Prefer readability over efficiency
* Comments are good
* snake case file names
* upper camel case function names, name space names

Guidelines for 1d sampling submissions:
* generate values to sample in [0,1]
* stateless one shot generation: function signature requirements
* progressive: derive from a class that has a pure virtual to implement. So, you can have state if you want to, but don't have to i guess?
 * would need to hook up to different tests
* random: store random parts in a cache? dunno...
* make .h and a .cpp.
 * naming conventions! of files, namespaces, directories
 * keep the header as minimal as possible to keep from poluting global symbols.
 * include your .h in the _1d.h file

*/
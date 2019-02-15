function scandir(command)
    local i, t, popen = 0, {}, io.popen
    local pfile = popen(command)
    for filename in pfile:lines() do
        i = i + 1
        t[i] = filename
    end
    pfile:close()
    return t
end

print "=====Generating Code====="

local dotHHeader = "// Autogenerated by codegen.lua during premake process\n\n#pragma once\n\n"
local file

-- make ./build/codegen/codegen.h
file = io.open("./build/codegen/codegen.h", "w")
file:write(dotHHeader)
file:write('#define _CRT_SECURE_NO_WARNINGS // for stb\n\n')
file:write("#include <vector>\n\n")
file:write("using SampleGenerate_1d = void(*)(std::vector<float>& values, size_t numValues);\n\n")
file:write("struct SampleGenerateInfo_1d\n{\n")
file:write("    SampleGenerate_1d function;\n")
file:write("    const char* sampleFamily;\n")
file:write("    const char* sampleType;\n")
file:write("    const char* name;\n")
file:write("};\n\n")
file:write("using Test_1d = void(*)(SampleGenerateInfo_1d* sampleFunctions, size_t sampleFunctionCount, size_t* sampleCounts, size_t sampleCountCounts);\n\n")
file:write("#define countof(array) (sizeof(array) / sizeof(array[0]))\n\n");
file:write('#include "tests/tests.h"\n')
file:write('#include "samples/samples.h"\n')
file:close()

-- make ./build/codegen/samples/samples.h
file = io.open("./build/codegen/samples/samples.h", "w")
file:write(dotHHeader)
local sampleFamilies = scandir('cd ./src/samples/ && ls -d ./*/ && cd ../..')
for k,v in pairs(sampleFamilies) do
	local sampleFamily = string.sub(v,3,-2)
	file:write('#include "'..sampleFamily..'/samples.h"\n')
end
file:close()

-- make ./build/codegen/samples/X/samples.h
for k,v in pairs(sampleFamilies) do
	local sampleFamily = string.sub(v,3,-2)
	file = io.open("./build/codegen/samples/"..sampleFamily.."/samples.h", "w")
	file:write(dotHHeader)
	local sampleTypes = scandir('cd ./src/samples/'..sampleFamily..'/ && ls -d ./*/ && cd ../../..')
	for k2,v2 in pairs(sampleTypes) do
		local sampleType = string.sub(v2,3,-2)
		file:write('#include "'..sampleType..'/samples.h"\n')
	end
	file:close()
end

-- make ./build/codegen/tests/tests.h
file = io.open("./build/codegen/tests/tests.h", "w")
file:write(dotHHeader)
local testTypes = scandir('cd ./src/tests/ && ls -d ./*/ && cd ../..')
for k,v in pairs(testTypes) do
	local testType = string.sub(v,3,-2)
	file:write('#include "'..testType..'/tests.h"\n')
end
file:close()

-- make ./build/codegen/tests/X/tests.h
for k,v in pairs(testTypes) do
	local testType = string.sub(v,3,-2)
	file = io.open("./build/codegen/tests/"..testType.."/tests.h", "w")
	file:write(dotHHeader)
	local subTestTypes = scandir('cd ./src/tests/'..testType..'/ && ls -d ./*/ && cd ../../..')
	for k2,v2 in pairs(subTestTypes) do
		local subTestType = string.sub(v2,3,-2)
		file:write('#include "'..subTestType..'/tests.h"\n')
	end
	file:close()
end

-- make ./build/codegen/tests/X/Y/tests.h
for k,v in pairs(testTypes) do
    local testType = string.sub(v,3,-2)
    local subTestTypes = scandir('cd ./src/tests/'..testType..'/ && ls -d ./*/ && cd ../../..')
    for k2,v2 in pairs(subTestTypes) do

        local subTestType = string.sub(v2,3,-2)

        file = io.open("./build/codegen/tests/"..testType.."/"..subTestType.."/tests.h", "w")
        file:write(dotHHeader)

        dofile("./src/tests/"..testType.."/"..subTestType.."/tests.lua")

        file:write("namespace Tests\n{\n    namespace "..testType.."\n    {\n        namespace "..info.CodeName.."\n        {\n")

        for functionIndex, functionName in ipairs(info.Functions) do
            file:write("            void "..functionName.."(SampleGenerateInfo_1d* sampleFunctions, size_t sampleFunctionCount, size_t* sampleCounts, size_t sampleCountCounts);\n")
        end

        file:write("        };\n    };\n};\n")
    end
end

-- make ./build/codegen/tests/X/Y/autotest.h
for k,v in pairs(testTypes) do
    local testType = string.sub(v,3,-2)
    local subTestTypes = scandir('cd ./src/tests/'..testType..'/ && ls -d ./*/ && cd ../../..')
    for k2,v2 in pairs(subTestTypes) do

        local subTestType = string.sub(v2,3,-2)

        dofile("./src/tests/"..testType.."/"..subTestType.."/tests.lua")

        file = io.open("./build/codegen/tests/"..testType.."/"..subTestType.."/autotest.h", "w")
        file:write(dotHHeader)

        file:write("namespace Tests\n{\n    namespace "..testType.."\n    {\n        namespace "..info.CodeName.."\n        {\n")

        file:write("            void AutoTest()\n            {\n")
        file:write("                SampleGenerateInfo"..testType.." funcs[] =\n                {\n")
        local sampleTypes = scandir('cd ./src/samples/'..testType..'/ && ls -d ./*/ && cd ../../..')
        for k3, v3 in pairs(sampleTypes) do
            local sampleType = string.sub(v3,3,-2)
            dofile("./src/samples/"..testType.."/"..sampleType.."/samples.lua")
            for functionIndex, functionName in ipairs(info.Functions) do
                file:write("                    { Samples::"..testType.."::"..info.CodeName.."::"..functionName..", \""..testType.."\", \""..sampleType.."\", \""..functionName.."\"},\n")
            end
        end
        file:write("                };\n\n")

        file:write("                size_t sampleCounts[] =\n                {\n")
        dofile("./src/tests/"..testType.."/"..subTestType.."/tests.lua")
        for sampleCountIndex, sampleCount in ipairs(info.AutoTestSampleCounts) do
            file:write("                    "..sampleCount..",\n")
        end
        file:write("                };\n\n")
        for functionIndex, functionName in ipairs(info.Functions) do
            file:write("                "..functionName.."(funcs, countof(funcs), sampleCounts, countof(sampleCounts));\n")
        end

        file:write("            }\n")
        file:write("        };\n    };\n};\n")
    end
end

-- make ./build/codegen/samples/X/Y/samples.h
for k,v in pairs(sampleFamilies) do
    local sampleFamily = string.sub(v,3,-2)
    local sampleTypes = scandir('cd ./src/samples/'..sampleFamily..'/ && ls -d ./*/ && cd ../../..')
    for k2,v2 in pairs(sampleTypes) do

        local sampleType = string.sub(v2,3,-2)

        file = io.open("./build/codegen/samples/"..sampleFamily.."/"..sampleType.."/samples.h", "w")
        file:write(dotHHeader)

        dofile("./src/samples/"..sampleFamily.."/"..sampleType.."/samples.lua")

        file:write("namespace Samples\n{\n    namespace "..sampleFamily.."\n    {\n        namespace "..info.CodeName.."\n        {\n")

        for functionIndex, functionName in ipairs(info.Functions) do
            file:write("            void "..functionName.."(std::vector<float>& values, size_t numValues);\n")
        end

        file:write("        };\n    };\n};\n")

        -- also make output/samples/X/Y/
        os.mkdir("./output/samples/"..sampleFamily.."/"..sampleType.."/")
    end
end

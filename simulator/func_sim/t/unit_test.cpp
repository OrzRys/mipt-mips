// generic C
#include <cassert>
#include <cstdlib>

// Google Test library
#include <gtest/gtest.h>

// Module
#include "../func_sim.h"

static const std::string valid_elf_file = TEST_PATH;
static const int64 num_steps = 2250;

#define GTEST_ASSERT_NO_DEATH(statement) \
    ASSERT_EXIT({{ statement } ::exit(EXIT_SUCCESS); }, ::testing::ExitedWithCode(0), "")

TEST( Func_Sim_init, Process_Wrong_Args_Of_Constr)
{
    // Just call a constructor
    ASSERT_NO_THROW( FuncSim mips );

    // Call constructor and init
    ASSERT_NO_THROW( FuncSim().init( valid_elf_file) );

    // Do bad init
    ASSERT_EXIT( FuncSim().init( "./1234567890/qwertyuop"),
                 ::testing::ExitedWithCode( EXIT_FAILURE), "ERROR.*");
}

TEST( Func_Sim, Make_A_Step)
{
    FuncSim mips;
    mips.init( valid_elf_file);
    ASSERT_EQ( mips.step().Dump(), "0x4000f0: lui $at, 0x41\t [ $at = 0x410000]");
}

TEST( Func_Sim, Run_Full_Trace)
{
    FuncSim mips;
    GTEST_ASSERT_NO_DEATH( mips.run( valid_elf_file, num_steps); );
}

int main( int argc, char* argv[])
{
    ::testing::InitGoogleTest( &argc, argv);
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";
    return RUN_ALL_TESTS();
}


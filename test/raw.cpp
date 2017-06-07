#include <msgpack11.hpp>

#include <gtest/gtest.h>

TEST(MSGPACK_BINARY, pack_unpack)
{
    msgpack11::MsgPack::binary data{ 0xaau, 0x55u, 0xffu };

    msgpack11::MsgPack packed{data};
    msgpack11::MsgPack::String dumped = packed.dump();

    EXPECT_EQ(static_cast<uint8_t>(dumped[0]), 0xc4u);
    EXPECT_EQ(static_cast<uint8_t>(dumped[1]), 0x03u);
    EXPECT_EQ(static_cast<uint8_t>(dumped[2]), 0xaau);
    EXPECT_EQ(static_cast<uint8_t>(dumped[3]), 0x55u);
    EXPECT_EQ(static_cast<uint8_t>(dumped[4]), 0xffu);

    msgpack11::MsgPack::String err;
    msgpack11::MsgPack parsed = msgpack11::MsgPack::parse(dumped, err);

    EXPECT_TRUE(packed == parsed);
}

TEST(MSGPACK_BINARY, pack_unpack_8_l)
{
    msgpack11::MsgPack::binary data;

    msgpack11::MsgPack packed{data};
    msgpack11::MsgPack::String dumped = packed.dump();

    EXPECT_EQ(static_cast<uint8_t>(dumped[0]), 0xc4u);
    EXPECT_EQ(static_cast<uint8_t>(dumped[1]), 0x00u);

    msgpack11::MsgPack::String err;
    msgpack11::MsgPack parsed = msgpack11::MsgPack::parse(dumped, err);

    EXPECT_TRUE(packed == parsed);
}

TEST(MSGPACK_BINARY, pack_unpack_8_h)
{
    msgpack11::MsgPack::binary data(0xffu, 0xaau);

    msgpack11::MsgPack packed{data};
    msgpack11::MsgPack::String dumped = packed.dump();

    EXPECT_EQ(static_cast<uint8_t>(dumped[0]), 0xc4u);
    EXPECT_EQ(static_cast<uint8_t>(dumped[1]), 0xffu);
    EXPECT_EQ(static_cast<uint8_t>(dumped[2]), 0xaau);

    msgpack11::MsgPack::String err;
    msgpack11::MsgPack parsed = msgpack11::MsgPack::parse(dumped, err);

    EXPECT_TRUE(packed == parsed);
}

TEST(MSGPACK_BINARY, pack_unpack_16_l)
{
    msgpack11::MsgPack::binary data(0x100u, 0xaau);

    msgpack11::MsgPack packed{data};
    msgpack11::MsgPack::String dumped = packed.dump();

    EXPECT_EQ(static_cast<uint8_t>(dumped[0]), 0xc5u);
    EXPECT_EQ(static_cast<uint8_t>(dumped[1]), 0x01u);
    EXPECT_EQ(static_cast<uint8_t>(dumped[2]), 0x00u);
    EXPECT_EQ(static_cast<uint8_t>(dumped[3]), 0xaau);

    msgpack11::MsgPack::String err;
    msgpack11::MsgPack parsed = msgpack11::MsgPack::parse(dumped, err);

    EXPECT_TRUE(packed == parsed);
}

TEST(MSGPACK_BINARY, pack_unpack_16_h)
{
    msgpack11::MsgPack::binary data(0xffffu, 0xaau);

    msgpack11::MsgPack packed{data};
    msgpack11::MsgPack::String dumped = packed.dump();

    EXPECT_EQ(static_cast<uint8_t>(dumped[0]), 0xc5u);
    EXPECT_EQ(static_cast<uint8_t>(dumped[1]), 0xffu);
    EXPECT_EQ(static_cast<uint8_t>(dumped[2]), 0xffu);
    EXPECT_EQ(static_cast<uint8_t>(dumped[3]), 0xaau);

    msgpack11::MsgPack::String err;
    msgpack11::MsgPack parsed = msgpack11::MsgPack::parse(dumped, err);

    EXPECT_TRUE(packed == parsed);
}

TEST(MSGPACK_BINARY, pack_unpack_32_l)
{
    msgpack11::MsgPack::binary data(0x10000u, 0xaau);

    msgpack11::MsgPack packed{data};
    msgpack11::MsgPack::String dumped = packed.dump();

    EXPECT_EQ(static_cast<uint8_t>(dumped[0]), 0xc6u);
    EXPECT_EQ(static_cast<uint8_t>(dumped[1]), 0x00u);
    EXPECT_EQ(static_cast<uint8_t>(dumped[2]), 0x01u);
    EXPECT_EQ(static_cast<uint8_t>(dumped[3]), 0x00u);
    EXPECT_EQ(static_cast<uint8_t>(dumped[4]), 0x00u);
    EXPECT_EQ(static_cast<uint8_t>(dumped[5]), 0xaau);

    msgpack11::MsgPack::String err;
    msgpack11::MsgPack parsed = msgpack11::MsgPack::parse(dumped, err);

    EXPECT_TRUE(packed == parsed);
}

TEST(MSGPACK_STRING, pack_unpack)
{
    msgpack11::MsgPack::String s = "ABC";

    msgpack11::MsgPack packed{s};
    msgpack11::MsgPack::String dumped = packed.dump();

    EXPECT_EQ(static_cast<uint8_t>(dumped[0]), 0xa3u);
    EXPECT_EQ(static_cast<uint8_t>(dumped[1]), 'A');
    EXPECT_EQ(static_cast<uint8_t>(dumped[2]), 'B');
    EXPECT_EQ(static_cast<uint8_t>(dumped[3]), 'C');

    msgpack11::MsgPack::String err;
    msgpack11::MsgPack parsed = msgpack11::MsgPack::parse(dumped, err);

    EXPECT_TRUE(packed == parsed);
}

TEST(MSGPACK_STRING, pack_unpack_fix_l)
{
    msgpack11::MsgPack::String s;

    msgpack11::MsgPack packed{s};
    msgpack11::MsgPack::String dumped = packed.dump();

    EXPECT_EQ(static_cast<uint8_t>(dumped[0]), 0xa0u);

    msgpack11::MsgPack::String err;
    msgpack11::MsgPack parsed = msgpack11::MsgPack::parse(dumped, err);

    EXPECT_TRUE(packed == parsed);
}

TEST(MSGPACK_STRING, pack_unpack_fix_h)
{
    msgpack11::MsgPack::String s(0x1f, 'A');

    msgpack11::MsgPack packed{s};
    msgpack11::MsgPack::String dumped = packed.dump();

    EXPECT_EQ(static_cast<uint8_t>(dumped[0]), 0xbfu);
    EXPECT_EQ(static_cast<uint8_t>(dumped[1]), 'A');

    msgpack11::MsgPack::String err;
    msgpack11::MsgPack parsed = msgpack11::MsgPack::parse(dumped, err);

    EXPECT_TRUE(packed == parsed);
}

TEST(MSGPACK_STRING, pack_unpack_8)
{
    msgpack11::MsgPack::String s(0x1f+1, 'A');

    msgpack11::MsgPack packed{s};
    msgpack11::MsgPack::String dumped = packed.dump();

    EXPECT_EQ(static_cast<uint8_t>(dumped[0]), 0xd9u);
    EXPECT_EQ(static_cast<uint8_t>(dumped[1]), 0x20u);
    EXPECT_EQ(static_cast<uint8_t>(dumped[2]), 'A');

    msgpack11::MsgPack::String err;
    msgpack11::MsgPack parsed = msgpack11::MsgPack::parse(dumped, err);

    EXPECT_TRUE(packed == parsed);
}

TEST(MSGPACK_STRING, pack_unpack_16_l)
{
    msgpack11::MsgPack::String s(0x100, 'A');

    msgpack11::MsgPack packed{s};
    msgpack11::MsgPack::String dumped = packed.dump();

    EXPECT_EQ(static_cast<uint8_t>(dumped[0]), 0xdau);
    EXPECT_EQ(static_cast<uint8_t>(dumped[1]), 0x01u);
    EXPECT_EQ(static_cast<uint8_t>(dumped[2]), 0x00u);
    EXPECT_EQ(static_cast<uint8_t>(dumped[3]), 'A');

    msgpack11::MsgPack::String err;
    msgpack11::MsgPack parsed = msgpack11::MsgPack::parse(dumped, err);

    EXPECT_TRUE(packed == parsed);
}


TEST(MSGPACK_STRING, pack_unpack_16_h)
{
    msgpack11::MsgPack::String s(0xffff, 'A');

    msgpack11::MsgPack packed{s};
    msgpack11::MsgPack::String dumped = packed.dump();

    EXPECT_EQ(static_cast<uint8_t>(dumped[0]), 0xdau);
    EXPECT_EQ(static_cast<uint8_t>(dumped[1]), 0xffu);
    EXPECT_EQ(static_cast<uint8_t>(dumped[2]), 0xffu);
    EXPECT_EQ(static_cast<uint8_t>(dumped[3]), 'A');

    msgpack11::MsgPack::String err;
    msgpack11::MsgPack parsed = msgpack11::MsgPack::parse(dumped, err);

    EXPECT_TRUE(packed == parsed);
}

TEST(MSGPACK_STRING, pack_unpack_32_l)
{
    msgpack11::MsgPack::String s(0xffff+1, 'A');

    msgpack11::MsgPack packed{s};
    msgpack11::MsgPack::String dumped = packed.dump();

    EXPECT_EQ(static_cast<uint8_t>(dumped[0]), 0xdbu);
    EXPECT_EQ(static_cast<uint8_t>(dumped[1]), 0x00u);
    EXPECT_EQ(static_cast<uint8_t>(dumped[2]), 0x01u);
    EXPECT_EQ(static_cast<uint8_t>(dumped[3]), 0x00u);
    EXPECT_EQ(static_cast<uint8_t>(dumped[4]), 0x00u);
    EXPECT_EQ(static_cast<uint8_t>(dumped[5]), 'A');

    msgpack11::MsgPack::String err;
    msgpack11::MsgPack parsed = msgpack11::MsgPack::parse(dumped, err);

    EXPECT_TRUE(packed == parsed);
}

#pragma once

struct MESSAGE_ID
{
public:
	int _type;
	int _id;

private:
	int _x;
	int _y;
};

struct MESSAGE_ADD
{
public:
	int _type;
	int _id;
	int _x;
	int _y;
};

struct MESSAGE_DELETE
{
public:
	int _type;
	int _id;

private:
	int _x;
	int _y;
};

struct MESSAGE_MOVE
{
public:
	int _type;
	int _id;
	int _x;
	int _y;
};

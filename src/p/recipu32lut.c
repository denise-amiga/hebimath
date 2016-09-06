/*
 * hebimath - arbitrary precision arithmetic library
 * See LICENSE file for copyright and license details
 */

/*
 * NOTE: This source file is not intended to be compiled directly.
 * It should be included by a kernel-backend specific source file.
 */

uint16_t hebi_recipu32_v0lut__[512] =
{
	0x7FE1, 0x7FA1, 0x7F61, 0x7F22, 0x7EE3, 0x7EA4, 0x7E65, 0x7E27,
	0x7DE9, 0x7DAB, 0x7D6D, 0x7D30, 0x7CF3, 0x7CB6, 0x7C79, 0x7C3D,
	0x7C00, 0x7BC4, 0x7B89, 0x7B4D, 0x7B12, 0x7AD7, 0x7A9C, 0x7A61,
	0x7A27, 0x79EC, 0x79B2, 0x7979, 0x793F, 0x7906, 0x78CC, 0x7894,
	0x785B, 0x7822, 0x77EA, 0x77B2, 0x777A, 0x7742, 0x770B, 0x76D3,
	0x769C, 0x7665, 0x762F, 0x75F8, 0x75C2, 0x758C, 0x7556, 0x7520,
	0x74EA, 0x74B5, 0x7480, 0x744B, 0x7416, 0x73E2, 0x73AD, 0x7379,
	0x7345, 0x7311, 0x72DD, 0x72AA, 0x7277, 0x7243, 0x7210, 0x71DE,
	0x71AB, 0x7179, 0x7146, 0x7114, 0x70E2, 0x70B1, 0x707F, 0x704E,
	0x701C, 0x6FEB, 0x6FBA, 0x6F8A, 0x6F59, 0x6F29, 0x6EF9, 0x6EC8,
	0x6E99, 0x6E69, 0x6E39, 0x6E0A, 0x6DDB, 0x6DAB, 0x6D7D, 0x6D4E,
	0x6D1F, 0x6CF1, 0x6CC2, 0x6C94, 0x6C66, 0x6C38, 0x6C0A, 0x6BDD,
	0x6BB0, 0x6B82, 0x6B55, 0x6B28, 0x6AFB, 0x6ACF, 0x6AA2, 0x6A76,
	0x6A49, 0x6A1D, 0x69F1, 0x69C6, 0x699A, 0x696E, 0x6943, 0x6918,
	0x68ED, 0x68C2, 0x6897, 0x686C, 0x6842, 0x6817, 0x67ED, 0x67C3,
	0x6799, 0x676F, 0x6745, 0x671B, 0x66F2, 0x66C8, 0x669F, 0x6676,
	0x664D, 0x6624, 0x65FC, 0x65D3, 0x65AA, 0x6582, 0x655A, 0x6532,
	0x650A, 0x64E2, 0x64BA, 0x6493, 0x646B, 0x6444, 0x641C, 0x63F5,
	0x63CE, 0x63A7, 0x6381, 0x635A, 0x6333, 0x630D, 0x62E7, 0x62C1,
	0x629A, 0x6275, 0x624F, 0x6229, 0x6203, 0x61DE, 0x61B8, 0x6193,
	0x616E, 0x6149, 0x6124, 0x60FF, 0x60DA, 0x60B6, 0x6091, 0x606D,
	0x6049, 0x6024, 0x6000, 0x5FDC, 0x5FB8, 0x5F95, 0x5F71, 0x5F4D,
	0x5F2A, 0x5F07, 0x5EE3, 0x5EC0, 0x5E9D, 0x5E7A, 0x5E57, 0x5E35,
	0x5E12, 0x5DEF, 0x5DCD, 0x5DAB, 0x5D88, 0x5D66, 0x5D44, 0x5D22,
	0x5D00, 0x5CDE, 0x5CBD, 0x5C9B, 0x5C7A, 0x5C58, 0x5C37, 0x5C16,
	0x5BF5, 0x5BD4, 0x5BB3, 0x5B92, 0x5B71, 0x5B51, 0x5B30, 0x5B10,
	0x5AEF, 0x5ACF, 0x5AAF, 0x5A8F, 0x5A6F, 0x5A4F, 0x5A2F, 0x5A0F,
	0x59EF, 0x59D0, 0x59B0, 0x5991, 0x5972, 0x5952, 0x5933, 0x5914,
	0x58F5, 0x58D6, 0x58B7, 0x5899, 0x587A, 0x585B, 0x583D, 0x581F,
	0x5800, 0x57E2, 0x57C4, 0x57A6, 0x5788, 0x576A, 0x574C, 0x572E,
	0x5711, 0x56F3, 0x56D5, 0x56B8, 0x569B, 0x567D, 0x5660, 0x5643,
	0x5626, 0x5609, 0x55EC, 0x55CF, 0x55B2, 0x5596, 0x5579, 0x555D,
	0x5540, 0x5524, 0x5507, 0x54EB, 0x54CF, 0x54B3, 0x5497, 0x547B,
	0x545F, 0x5443, 0x5428, 0x540C, 0x53F0, 0x53D5, 0x53B9, 0x539E,
	0x5383, 0x5368, 0x534C, 0x5331, 0x5316, 0x52FB, 0x52E0, 0x52C6,
	0x52AB, 0x5290, 0x5276, 0x525B, 0x5240, 0x5226, 0x520C, 0x51F1,
	0x51D7, 0x51BD, 0x51A3, 0x5189, 0x516F, 0x5155, 0x513B, 0x5121,
	0x5108, 0x50EE, 0x50D5, 0x50BB, 0x50A2, 0x5088, 0x506F, 0x5056,
	0x503C, 0x5023, 0x500A, 0x4FF1, 0x4FD8, 0x4FBF, 0x4FA6, 0x4F8E,
	0x4F75, 0x4F5C, 0x4F44, 0x4F2B, 0x4F13, 0x4EFA, 0x4EE2, 0x4ECA,
	0x4EB1, 0x4E99, 0x4E81, 0x4E69, 0x4E51, 0x4E39, 0x4E21, 0x4E09,
	0x4DF1, 0x4DDA, 0x4DC2, 0x4DAA, 0x4D93, 0x4D7B, 0x4D64, 0x4D4D,
	0x4D35, 0x4D1E, 0x4D07, 0x4CF0, 0x4CD8, 0x4CC1, 0x4CAA, 0x4C93,
	0x4C7D, 0x4C66, 0x4C4F, 0x4C38, 0x4C21, 0x4C0B, 0x4BF4, 0x4BDE,
	0x4BC7, 0x4BB1, 0x4B9A, 0x4B84, 0x4B6E, 0x4B58, 0x4B41, 0x4B2B,
	0x4B15, 0x4AFF, 0x4AE9, 0x4AD3, 0x4ABD, 0x4AA8, 0x4A92, 0x4A7C,
	0x4A66, 0x4A51, 0x4A3B, 0x4A26, 0x4A10, 0x49FB, 0x49E5, 0x49D0,
	0x49BB, 0x49A6, 0x4990, 0x497B, 0x4966, 0x4951, 0x493C, 0x4927,
	0x4912, 0x48FE, 0x48E9, 0x48D4, 0x48BF, 0x48AB, 0x4896, 0x4881,
	0x486D, 0x4858, 0x4844, 0x482F, 0x481B, 0x4807, 0x47F3, 0x47DE,
	0x47CA, 0x47B6, 0x47A2, 0x478E, 0x477A, 0x4766, 0x4752, 0x473E,
	0x472A, 0x4717, 0x4703, 0x46EF, 0x46DB, 0x46C8, 0x46B4, 0x46A1,
	0x468D, 0x467A, 0x4666, 0x4653, 0x4640, 0x462C, 0x4619, 0x4606,
	0x45F3, 0x45E0, 0x45CD, 0x45BA, 0x45A7, 0x4594, 0x4581, 0x456E,
	0x455B, 0x4548, 0x4536, 0x4523, 0x4510, 0x44FE, 0x44EB, 0x44D8,
	0x44C6, 0x44B3, 0x44A1, 0x448F, 0x447C, 0x446A, 0x4458, 0x4445,
	0x4433, 0x4421, 0x440F, 0x43FD, 0x43EB, 0x43D9, 0x43C7, 0x43B5,
	0x43A3, 0x4391, 0x437F, 0x436D, 0x435C, 0x434A, 0x4338, 0x4327,
	0x4315, 0x4303, 0x42F2, 0x42E0, 0x42CF, 0x42BD, 0x42AC, 0x429B,
	0x4289, 0x4278, 0x4267, 0x4256, 0x4244, 0x4233, 0x4222, 0x4211,
	0x4200, 0x41EF, 0x41DE, 0x41CD, 0x41BC, 0x41AB, 0x419A, 0x418A,
	0x4179, 0x4168, 0x4157, 0x4147, 0x4136, 0x4125, 0x4115, 0x4104,
	0x40F4, 0x40E3, 0x40D3, 0x40C2, 0x40B2, 0x40A2, 0x4091, 0x4081,
	0x4071, 0x4061, 0x4050, 0x4040, 0x4030, 0x4020, 0x4010, 0x4000
};

#if 0

/* hebi_recipu32_v0lut__ is generated with the following program: */

#include <stdio.h>

int main(int argc, char **argv)
{
	int x, i, j;

	puts("uint16_t hebi_recipu32_v0lut__[512] =");
	puts("{");

	for (i = 0; i < 64; ++i) {
		putchar('\t');
		for (j = 0; j < 8; ++j) {
			x = 16761344 / (512 + i*8 + j);
			printf("0x%04X", x);
			if (i != 63 || j != 7)
				printf(j == 7 ? "," : ", ");
		}
		putchar('\n');
	}

	puts("};");
	return 0;
}

#endif
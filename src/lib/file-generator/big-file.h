#pragma once

#include <cstdint>

struct ITEM_VENDA
{
	uint32_t id;
	uint32_t id_venda;
	uint32_t data;
	float desconto;
	char desc[1008];

	bool operator<=(const ITEM_VENDA other)
	{
		return id <= other.id;
	}

	bool operator>=(const ITEM_VENDA other)
	{
		return id >= other.id;
	}
};

void gerar_array_iv(const char *arquivo_saida, unsigned int n_registros, int seed);

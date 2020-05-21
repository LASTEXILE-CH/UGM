#pragma once

#include "IMatrix.h"
#include "../IMul.h"
#include "IMatrixMul_detail.h"

namespace Ubpa {
	template<typename Base, typename Impl>
	struct IMatrixMul : Base {
		using Base::Base;

		static constexpr size_t N = ImplTraits_N<Impl>;
		using F = ImplTraits_F<Impl>;

		using Base::operator*;

		using Vector = ImplTraits_T<Impl>;

		inline const Vector operator*(const Vector& v) const noexcept {
			auto& m = static_cast<const Impl&>(*this);
			return detail::IMatrixMul::mul<N>::run(m, v);
		}

	private:
		template<typename Base, typename Impl>
		friend struct IMul;

		inline const Impl impl_mul(const Impl& y) const noexcept {
			auto& x = static_cast<const Impl&>(*this);
			return detail::IMatrixMul::mul<N>::run(x, y);
		}

		inline const Impl impl_inverse() const noexcept {
			auto& m = static_cast<const Impl&>(*this);
			return detail::IMatrixMul::inverse<N>::run(m);
		}
	};

	InterfaceTraits_Regist(IMatrixMul,
		IMul, IMatrix);
}

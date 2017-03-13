#pragma once
#include "Player.h"
#include "InfectionCard.h"
#include "EpidemicCard.h"
#include "CityCard.h"
#include "EventCard.h"
#include "Settings.h"

template<typename Archive>
static void registerTypes(Archive& ar)
{
	using namespace pan;
	ar.template register_type<Dispatcher>();
	ar.template register_type<FOperative>();
	ar.template register_type<Generalist>();
	ar.template register_type<Medic>();
	ar.template register_type<QSpecialist>();
	ar.template register_type<Researcher>();
	ar.template register_type<InfectionCard>();
	ar.template register_type<EpidemicCard>();
	ar.template register_type<EventCard>();
	ar.template register_type<CityCard>();
	ar.template register_type<CardBase>();
	ar.template register_type<Settings>();
}

#define SPECIALIZE_POINTER_SAVE_LOAD(T) \
namespace boost { \
	namespace serialization { \
		template<class Archive> \
		inline void save_construct_data(Archive & ar, const T * p, const unsigned int file_version){} \
		template<class Archive> \
		inline void load_construct_data(Archive & ar, T * p, const unsigned int file_version){} \
		} \
} 

SPECIALIZE_POINTER_SAVE_LOAD(pan::CardBase)

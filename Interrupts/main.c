/*
 * main.c
 *
 *  Created on: 9 sie 2026
 *      Author: cichy
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h> // Biblioteka przerwań
#ifndef F_CPU
#define F_CPU 8000000UL // 8 MHz
#endif
//---------------------------------------PRZERWANIA ZEWNETRZNE--------------------
//PRZYKŁAD
//int main(void) {
//    // 1. Konfiguracja pinu diody (PC0 jako wyjście)
//    DDRC |= (1 << PC0);
//    PORTC |= (1 << PC0); // Dioda zgaszona na start (sterowanie zerem)
//
//    // 2. Konfiguracja pinu przycisku (PD2/INT0 jako wejście z Pull-Up)
//    DDRD &= ~(1 << PD2);
//    PORTD |= (1 << PD2);
//
//    // KROK 1: Wyzwalanie zboczem opadającym na INT0 (ISC01 = 1, ISC00 = 0)
//    MCUCR |= (1 << ISC01);
//    MCUCR &= ~(1 << ISC00); // dla pewności zerujemy ISC00
//
//    // KROK 2: Włączenie przerwania INT0
//    GICR |= (1 << INT0);
//
//    // KROK 3: Globalne włączenie przerwań
//    sei();
//
//    // Pętla główna – procesor może robić coś zupełnie innego albo odpoczywać
//    while (1) {
//        // Pusto! Przycisk jest obsługiwany sprzętowo w tle!
//    }
//}
//
//// Obsługa przerwania zewnętrznego INT0
//ISR(INT0_vect) {
//    // Odwracamy stan diody na PC0 (XOR) za każdym wciśnięciem przycisku
//    PORTC ^= (1 << PC0);
//}


//ZADANIE 1 Zamiana diodek za pomoca przycisku (przerwania zewnetrznego)

//int main(void){
//
//	DDRD &= ~(1 << PD3);
//	PORTD |= (1 << PD3);
//
//	DDRC |= (1 << PC0);
//	DDRC |= (1 << PC1);
//
//	PORTC |= (1 << PC0);
//	PORTC &= ~(1 << PC1);
//
//	GICR |= (1 << INT1);
//
//	MCUCR |= (1 << ISC11);
//	MCUCR &= ~(1 << ISC10);
//
//
//	sei();
//
//	while(1){
//	}
//}
//
////Moduł obslugiwania przerwan
//ISR(INT1_vect){
//	PORTC ^= (1 << PC0);
//	PORTC ^= (1 << PC1);
//}

//ZADANIE 2 Dwuprzyciskowy Sterownik Stanu

//volatile uint8_t poziom = 0;
//int main(void){
//
//
//	DDRC |= (1 << PC0);
//	DDRC |= (1 << PC1);
//	DDRC |= (1 << PC2);
//
//	PORTC |= (1 << PC0);
//	PORTC |= (1 << PC1);
//	PORTC |= (1 << PC2);
//
//	DDRD &= ~(1 << PD2);
//	PORTD |= (1 << PD2);
//
//	DDRD &= ~(1 << PD3);
//	PORTD |= (1 << PD3);
//
//	GICR |= (1 << INT0);
//	GICR |= (1 << INT1);
//
//	MCUCR |= (1 << ISC01);
//	MCUCR &= ~(1 << ISC00);
//	MCUCR |= (1 << ISC11);
//	MCUCR &= ~(1 << ISC10);
//
//	sei();
//	while(1){
//		PORTC = ~(1 << poziom);
//	}
//}
//
//ISR(INT0_vect){
//	if(poziom > 0){
//	poziom = poziom - 1;
//	}
//}
//
//ISR(INT1_vect){
//	if(poziom < 2){
//	poziom = poziom + 1;
//	}
//}
// ZADANIE 3 System alarmowy z przerwaniem sztabowym (Reset)

//volatile uint8_t alarm_aktywny = 0;
//
//int main(void){
//
//	DDRC |= (1<<PC0);
//	DDRC |= (1<<PC1);
//
//	PORTC &= ~(1 << PC0);
//	PORTC |= (1 << PC1);
//
//	DDRD &= ~(1 << PD2);
//	DDRD &= ~(1 << PD3);
//
//	PORTD |= (1 << PD2);
//	PORTD |= (1 << PD3);
//
//	MCUCR |= (1 << ISC01);
//	MCUCR &= ~(1 << ISC00);
//
//	MCUCR |= (1 << ISC11);
//	MCUCR &= ~(1 << ISC10);
//
//	GICR |= (1 << INT0);
//	GICR |= (1 << INT1);
//
//	sei();
//
//	while(1){
//		if(alarm_aktywny == 1){
//			PORTC |= (1 << PC0);
//
//			PORTC ^= (1 << PC1);
//			_delay_ms(10000);
//
//		}
//		if(alarm_aktywny == 0){
//			PORTC &= ~(1 << PC0);
//			PORTC |= (1 << PC1);
//		}
//
//	}
//}
//
//ISR(INT0_vect){
//	alarm_aktywny = 1;
//
//}
//
//ISR(INT1_vect){
//	alarm_aktywny = 0;
//}

//-----------------------PRZERWANIA WEWNĘTRZNE--------------------------

				//Tryb zwykłego licznika

//PRZYKŁAD
// Licznik przepełnień Timera
//int main(void) {
//    // 1. Dioda PC0 jako wyjście
//    DDRC |= (1 << PC0);
//    PORTC &= ~(1 << PC0); // Dioda świeci na start
//
//    // 2. Wpisujemy wartość początkową do 16-bitowego rejestru TCNT1
//    TCNT1 = 34286;  // 65536 - 31250 = 34286
//
//    // 3. Konfiguracja Preskalera 256 w rejestrze TCCR1B
//    // Dla Timera1 preskaler 256 to bit CS12 = 1
//    TCCR1B |= (1 << CS12);
//
//    // 4. Włączenie przerwania od przepełnienia Timera1 (TOIE1 w rejestrze TIMSK)
//    TIMSK |= (1 << TOIE1);
//
//    // 5. Globalne odblokowanie przerwań
//    sei();
//
//    while (1) {
//        // Pętla główna pusta!
//    }
//}
//
//// Przerwanie od przepełnienia Timera1 (wywołuje się CO RÓWNĄ SEKUNDĘ!)
//ISR(TIMER1_OVF_vect) {
//    // KLUCZOWY KROK: Od razu doładowujemy licznik na kolejną sekundę!
//    TCNT1 = 34286;
//
//    // Zmieniamy stan diody
//    PORTC ^= (1 << PC0);
//}

//ZADANIE 1 Zmiana diodek migajacych
//volatile uint8_t tryb = 0;
//
//int main(void){
//
//	DDRD &= ~(1 << PD3);
//	PORTD |= (1 << PD3);
//
//	DDRC |= (1 << PC0);
//	DDRC |= (1 << PC1);
//
//	PORTC &= ~(1 << PC0);
//	PORTC |= (1 << PC1);
//
//	MCUCR |= (1 << ISC11);
//	GICR |= (1 << INT1);
//
//	TCCR1B |= (1 << CS12);
//	TIMSK |= (1 << TOIE1);
//	TCNT1 = 49911;
//
//	sei();
//	while(1){
//
//	}
//}
//
//ISR(INT1_vect){
//	if(tryb == 0){
//		tryb = 1;
//	}
//	else{
//		tryb = 0;
//	}
//}
//
//ISR(TIMER1_OVF_vect){
//	TCNT1 = 49911;
//
//	if (tryb == 0){
//		PORTC |= (1 <<PC1);
//		PORTC ^= (1 <<PC0);
//	}else if(tryb == 1){
//		PORTC |= (1 <<PC0);
//		PORTC ^= (1 <<PC1);
//
//	}
//
//}

//Zadanie 2 Licznik impulsow
//volatile int licznik_klikniec = 0;
//int main(void){
//
//	DDRD &= ~(1 << PD3);
//	PORTD |= (1 << PD3);
//
//	DDRC |= (1 << PC0);
//	DDRC |= (1 << PC1);
//	DDRC |= (1 << PC3);
//
//	PORTC |= (1 << PC0);
//	PORTC |= (1 << PC1);
//
//	MCUCR |= (1 << ISC11);
//	GICR |= (1 << INT1);
//
//	TIMSK |= (1 << TOIE1);
//	TCCR1B |= (1 << CS12);
//	TCNT1 = 0;
//
//	sei();
//
//
//	while(1){
//	}
//
//}
//
//ISR(TIMER1_OVF_vect){
//		PORTC ^= (1 << PC3);
//
//		if(licznik_klikniec > 0){
//			int i = 0;
//			while(i < 2*licznik_klikniec){
//				PORTC ^= (1 << PC1);
//				_delay_ms(250);
//				i = i+1;
//			}
//			licznik_klikniec = 0;
//		}
//
//
//	}
//
//ISR(INT1_vect){
//	_delay_ms(30);
//
//
//	if(!(PIND & (1 << PD3))){
//			licznik_klikniec = licznik_klikniec + 1;
//			PORTC ^= (1 << PC0);
//			TCNT1 = 0;
//
//	}
//
//
//}

//Zadanie 3 Biegi predkosci migania

//volatile int bieg = 1;
//int main(void){
//
//	DDRC |= (1<<PC0);
//
//	DDRD &= ~(1<<PD2);
//	DDRD &= ~(1<<PD3);
//
//	PORTD |= (1 << PD2);
//	PORTD |= (1 << PD3);
//
//	MCUCR |= (1 << ISC01);
//	MCUCR |= (1 << ISC11);
//
//	GICR |= (1<< INT0);
//	GICR |= (1<< INT1);
//
//	TIMSK |= (1 << TOIE1);
//	TCCR1B |= (1 << CS12);
//	TCNT1 = 34286;
//
//	sei();
//
//	while(1){
//	}
//}
//
//ISR(TIMER1_OVF_vect){
//	if (bieg == 1){
//		PORTC ^= (1 << PC0);
//		TCNT1 = 34286;
//
//	}
//	else if(bieg == 2){
//		PORTC ^= (1 << PC0);
//		TCNT1 = 49911;
//	}
//	else{
//		PORTC ^= (1 << PC0);
//		TCNT1 = 62411;
//	}
//}
//
//ISR(INT0_vect){
//	_delay_ms(30);
//	if(!(PIND & (1<<PD2))){
//		if (bieg < 3){
//		bieg = bieg + 1;
//		}
//	}
//}
//
//ISR(INT1_vect){
//	_delay_ms(30);
//	if(!(PIND & (1<<PD3))){
//
//		if (bieg > 1){
//			bieg = bieg - 1;
//		}
//	}
//}
				// Tryb CTC

//Zadanie 1 Biegi predkosci migania CTC

//volatile int bieg = 1;
//int main(void){
//
//	DDRC |= (1<<PC0);
//
//	DDRD &= ~(1<<PD2);
//	DDRD &= ~(1<<PD3);
//
//	PORTD |= (1 << PD2);
//	PORTD |= (1 << PD3);
//
//	MCUCR |= (1 << ISC01);
//	MCUCR |= (1 << ISC11);
//
//	GICR |= (1<< INT0);
//	GICR |= (1<< INT1);
//
//	TIMSK |= (1 << OCIE1A);
//	TCCR1B |= (1 << CS12);
//	TCCR1B |= (1 << WGM12);
//
//	OCR1A = 31249;
//
//	sei();
//
//	while(1){
//	}
//}
//
//ISR(TIMER1_COMPA_vect){
//	PORTC ^= (1 << PC0);
//}
//
//ISR(INT0_vect){
//	_delay_ms(30);
//	if(!(PIND & (1<<PD2))){
//		if (bieg < 3){
//		bieg = bieg + 1;
//
//			if(bieg == 2)      OCR1A = 15624;
//			else if(bieg == 3) OCR1A = 3124;
//		}
//	}
//}
//
//ISR(INT1_vect){
//	_delay_ms(30);
//	if(!(PIND & (1<<PD3))){
//
//		if (bieg > 1){
//			bieg = bieg - 1;
//
//			if(bieg == 1)      OCR1A = 31249;
//			else if(bieg == 2) OCR1A = 15624;
//		}
//	}
//}

// Zadanie 2 "Sprzętowy Generator Częstotliwości" (Hardware Toggle) CTC

//volatile int bieg = 1;
//int main(void){
//	DDRD |= (1 << PD5);
//
//	DDRD &= ~(1<< PD3);
//	PORTD |= (1 << PD3);
//
//	MCUCR |= (1 << ISC11);
//	GICR |= (1 << INT1);
//
//	TCCR1B |= (1 << CS12);
//	TCCR1B |= (1 << WGM12);
//	OCR1A = 31249;
//
//	TCCR1A |= (1 << COM1A0);
//
//
//	sei();
//
//	while(1){
//
//	}
//}
//ISR(INT1_vect){
//	_delay_ms(30);
//
//	if(!(PIND & (1 << PD3))){
//		if(bieg == 1){
//			bieg = 2;
//			OCR1A = 3124;
//
//		}
//		else {
//			bieg = 1;
//			OCR1A = 31249;
//
//
//		}
//
//	}
//
//}
// Zadanie 3 Cyfrowy Stoper z Sygnalizacją Stanu
//int main(void){
//
//	DDRD &= ~(1 << PD2);
//	DDRD &= ~(1 << PD3);
//
//	PORTD |= (1<<PD2);
//	PORTD |= (1<<PD3);
//
//	DDRD |= (1<< PD5);
//	DDRC |= (1 << PC0);
//
//	PORTC |= (1 << PC0);
//
//	MCUCR |= (1 << ISC01);
//	MCUCR |= (1 << ISC11);
//
//	GICR |= (1 << INT0);
//	GICR |= (1 << INT1);
//
//	TCCR1B |= (1 << WGM12);
//	OCR1A = 31249;
//
//	TCCR1A |= (1 << COM1A0);
//
//	sei();
//
//	while(1){
//	}
//}
//
//
//ISR(INT0_vect){
//	_delay_ms(30);
//	if(!(PIND & (1 << PD2))){
//		PORTC |= (1 << PC0);
//		TCCR1B &= ~(1 << CS12);
//	}
//}
//
//ISR(INT1_vect){
//	_delay_ms(30);
//	if(!(PIND & (1 << PD3))){
//		PORTC &= ~(1 << PC0);
//		TCCR1B |= (1 << CS12);
//
//	}
//
//}

// Tryb PWM

//Zadanie 1 Jasnosc diodek gradient

//int main(void){
//	DDRC |= (1<< PC0);
//	DDRC |= (1<< PC3);
//	DDRD |= (1<< PD4);
//	DDRD |= (1<< PD5);
//
//	PORTC &= ~(1 << PC3);
//	PORTC |= (1 << PC0);
//
//	TCCR1A |= (1 << COM1A1);
//	TCCR1A |= (1 << COM1B1);
//
//	TCCR1A |= (1 << WGM10);
//
//	TCCR1B |= (1 << WGM12);
//	TCCR1B |= (1 << CS10);
//	TCCR1B |= (1 << CS11);
//
//	OCR1A = 125;
//	OCR1B = 25;
//
//
//	while(1){
//
//	}
//}
//Zadanie 2 Pulsowanie diodą

int main(void){

	DDRD |= (1 << PD5);
	TCCR1A |= (1 << COM1A1) | (1 << WGM10);
	TCCR1B |= (1 << CS11) | (1 << CS10);


	const uint8_t jasnosc_tab[] = {0, 1, 2, 4, 8, 12, 18, 28, 40, 60, 90, 130, 180, 255};
	while(1){
		for(int i = 0; i < 14; i++){
			OCR1A = jasnosc_tab[i];
			_delay_ms(60);
		}
		for(int i = 12; i >= 0; i--){
					OCR1A = jasnosc_tab[i];
					_delay_ms(60);
		}
	}
}



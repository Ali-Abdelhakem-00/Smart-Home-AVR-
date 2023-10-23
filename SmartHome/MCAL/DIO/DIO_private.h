
#ifndef DIO_private_h
#define DIO_private_h




//  volatile  3a4an(may3ml4 optimizing) el processor may5od5 2raito sabta gambo l2 ya5do kol mara 
// el address el bnktn feh makan 72i2i ba3d el ram 
#define PORTA_REG      *( (volatile u8*)0x3b )
#define DDRA_REG       *( (volatile u8*)0x3A )
#define PINA_REG       *( (volatile u8*)0x39 )


#define PORTB_REG      *( (volatile u8*)0x38 )
#define DDRB_REG       *( (volatile u8*)0x37 )
#define PINB_REG       *( (volatile u8*)0x36 )


#define PORTC_REG      *( (volatile u8*)0x35 )
#define DDRC_REG       *( (volatile u8*)0x34 )
#define PINC_REG       *( (volatile u8*)0x33 )


#define PORTD_REG      *( (volatile u8*)0x32 )
#define DDRD_REG       *( (volatile u8*)0x31 )
#define PIND_REG       *( (volatile u8*)0x30 )



#endif  

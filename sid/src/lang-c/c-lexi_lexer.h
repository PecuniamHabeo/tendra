
/*
 * Automatically generated by lexi version 2.0
 */

#ifndef LEXI_GENERATED_HEADER_c_lexi__INCLUDED
#define LEXI_GENERATED_HEADER_c_lexi__INCLUDED


/*
 * This struct holds state for the lexer; its representation is
 * private, but present here for ease of allocation.
 */
struct c_lexi_state {
	int (*zone)(struct c_lexi_state *);

	/*
	 * Lexi's buffer is a simple stack.
	 */
	int buffer[2];
	int buffer_index;
};

/* Read a character */
int c_lexi_readchar(struct c_lexi_state *state);

/* Push a character to lexi's buffer */
void c_lexi_push(struct c_lexi_state *state, const int c);

/* Pop a character from lexi's buffer */
int c_lexi_pop(struct c_lexi_state *state);

/* Flush lexi's buffer */
void c_lexi_flush(struct c_lexi_state *state);

#ifndef LEXI_EOF
#define LEXI_EOF -1
#endif

enum c_lexi_groups {
	c_lexi_group_white = 0x1,
	c_lexi_act_white = 0,
	c_lexi_group_act_identbody = 0x2,
	c_lexi_group_builtindlmt = 0x4,
	c_lexi_group_builtinbody = 0x8,
	c_lexi_group_builtinstart = 0x10,
	c_lexi_singleline_comment_white = 0,
	c_lexi_bracketed_comment_white = 0,
	c_lexi_group_identbody = 0x20,
	c_lexi_group_identstart = 0x40
};

/* true if the given character is present in the given group */
int c_lexi_group(enum c_lexi_groups group, int c);

/* Identify a token */
int c_lexi_read_token(struct c_lexi_state *state);

/* Initialise a c_lexi_state structure */
void c_lexi_init(struct c_lexi_state *state);

#endif


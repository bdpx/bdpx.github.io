/***********************************************************************
*                                                                      *
*   WMPI - Windows Message Passing Interface                           *
*   http://dsg.dei.uc.pt/wmpi                                          *
*                                                                      *
*   (C) 1999 by Dependable Systems Group                               *
*   CISUC - Centre of Informatics and Systems Research                 *
*   Department of Informatics Engineering                              *
*   University of Coimbra - Portugal                                   *
*                                                                      *
*   This is an MPI implementation for MS Windows                       *
*   It is based on the MPICH implementation from Argonne               *
*   National Laboratory and Mississippi State University,              *
*   version 1.1.2.                                                     *
*                                                                      *
***********************************************************************/

/* user include file for MPI programs */

#ifndef _MPI_INCLUDE
#define _MPI_INCLUDE

/* 
   NEW_POINTERS enables using ints for the MPI objects instead of addresses.
   This is required by MPI 1.1, particularly for Fortran (also for C, 
   since you can now have "constant" values for things like MPI_INT, and
   they are stronger than "constant between MPI_INIT and MPI_FINALIZE".
   For example, we might want to allow MPI_INT as a case label.

   NEW_POINTERS is the default; I'm purging all code that doesn't use
   NEW_POINTERS from the source.
 */
#define NEW_POINTERS

/* Keep C++ compilers from getting confused */
#if defined(__cplusplus)
extern "C" {
#endif

#if defined(__STDC__) || defined(__cplusplus) || defined(HAVE_PROTOTYPES)
#define MPIR_ARGS(a) a
#else
#define MPIR_ARGS(a) ()
#endif

 /* Results of the compare operations */
/* These should stay ordered */
#define MPI_IDENT     0
#define MPI_CONGRUENT 1
#define MPI_SIMILAR   2
#define MPI_UNEQUAL   3

/* Data types
 * A more aggressive yet homogeneous implementation might want to 
 * make the values here the number of bytes in the basic type, with
 * a simple test against a max limit (e.g., 16 for long double), and
 * non-contiguous structures with indices greater than that.
 */
typedef int MPI_Datatype;
#define MPI_CHAR           ((MPI_Datatype)1)
#define MPI_UNSIGNED_CHAR  ((MPI_Datatype)2)
#define MPI_BYTE           ((MPI_Datatype)3)
#define MPI_SHORT          ((MPI_Datatype)4)
#define MPI_UNSIGNED_SHORT ((MPI_Datatype)5)
#define MPI_INT            ((MPI_Datatype)6)
#define MPI_UNSIGNED       ((MPI_Datatype)7)
#define MPI_LONG           ((MPI_Datatype)8)
#define MPI_UNSIGNED_LONG  ((MPI_Datatype)9)
#define MPI_FLOAT          ((MPI_Datatype)10)
#define MPI_DOUBLE         ((MPI_Datatype)11)
#define MPI_LONG_DOUBLE    ((MPI_Datatype)12)
#define MPI_LONG_LONG_INT  ((MPI_Datatype)13)

#define MPI_PACKED         ((MPI_Datatype)14)
#define MPI_LB             ((MPI_Datatype)15)
#define MPI_UB             ((MPI_Datatype)16)

/* 
   The layouts for the types MPI_DOUBLE_INT etc are simply
   struct { 
       double var;
       int    loc;
   }
   This is documented in the man pages on the various datatypes.   
 */
#define MPI_FLOAT_INT      ((MPI_Datatype)17)
#define MPI_DOUBLE_INT     ((MPI_Datatype)18)
#define MPI_LONG_INT       ((MPI_Datatype)19)
#define MPI_SHORT_INT      ((MPI_Datatype)20)
#define MPI_2INT           ((MPI_Datatype)21)
#define MPI_LONG_DOUBLE_INT ((MPI_Datatype)22)

/* Fortran types */
#define MPI_COMPLEX        ((MPI_Datatype)23)
#define MPI_DOUBLE_COMPLEX ((MPI_Datatype)24)
#define MPI_LOGICAL        ((MPI_Datatype)25)
#define MPI_REAL           ((MPI_Datatype)26)
#define MPI_DOUBLE_PRECISION ((MPI_Datatype)27)
#define MPI_INTEGER        ((MPI_Datatype)28)
#define MPI_2INTEGER       ((MPI_Datatype)29)
#define MPI_2COMPLEX       ((MPI_Datatype)30)
#define MPI_2DOUBLE_COMPLEX   ((MPI_Datatype)31)
#define MPI_2REAL             ((MPI_Datatype)32)
#define MPI_2DOUBLE_PRECISION ((MPI_Datatype)33)
#define MPI_CHARACTER         ((MPI_Datatype)1)

/* Communicators */
typedef int MPI_Comm;
#define MPI_COMM_WORLD 91
#define MPI_COMM_SELF 92

/* Groups */
typedef int MPI_Group;
#define MPI_GROUP_EMPTY 90

/* Collective operations */
typedef int MPI_Op;

#define MPI_MAX    (MPI_Op)(100)
#define MPI_MIN    (MPI_Op)(101)
#define MPI_SUM    (MPI_Op)(102)
#define MPI_PROD   (MPI_Op)(103)
#define MPI_LAND   (MPI_Op)(104)
#define MPI_BAND   (MPI_Op)(105)
#define MPI_LOR    (MPI_Op)(106)
#define MPI_BOR    (MPI_Op)(107)
#define MPI_LXOR   (MPI_Op)(108)
#define MPI_BXOR   (MPI_Op)(109)
#define MPI_MINLOC (MPI_Op)(110)
#define MPI_MAXLOC (MPI_Op)(111)

/* Permanent key values */
/* C Versions (return pointer to value) */
#define MPI_TAG_UB 81
#define MPI_HOST 83
#define MPI_IO 85
#define MPI_WTIME_IS_GLOBAL 87
/* Fortran Versions (return integer value) */
#define MPIR_TAG_UB 80
#define MPIR_HOST 82
#define MPIR_IO 84
#define MPIR_WTIME_IS_GLOBAL 86

/* Define some null objects */
#define MPI_COMM_NULL      ((MPI_Comm)0)
#define MPI_OP_NULL        ((MPI_Op)0)
#define MPI_GROUP_NULL     ((MPI_Group)0)
#define MPI_DATATYPE_NULL  ((MPI_Datatype)0)
#define MPI_REQUEST_NULL   ((MPI_Request)0)
#define MPI_ERRHANDLER_NULL ((MPI_Errhandler )0)

/* These are only guesses; make sure you change them in mpif.h as well */
#define MPI_MAX_PROCESSOR_NAME 256
#define MPI_MAX_ERROR_STRING   512
#define MPI_MAX_NAME_STRING     63		/* How long a name do you need ? */

/* Pre-defined constants */
#define MPI_UNDEFINED      (-32766)
#define MPI_UNDEFINED_RANK MPI_UNDEFINED
#define MPI_KEYVAL_INVALID 0

/* Upper bound on the overhead in bsend for each message buffer */
#define MPI_BSEND_OVERHEAD 512

/* Topology types */
#define MPI_GRAPH  1
#define MPI_CART   2

#define MPI_BOTTOM      (void *)0

#define MPI_PROC_NULL   (-1)
#define MPI_ANY_SOURCE 	(-2)
#define MPI_ANY_TAG	(-1)

/* 
   Status object.  It is the only user-visible MPI data-structure 
   The "count" field is PRIVATE; use MPI_Get_count to access it. 
 */
typedef struct { 
    int count;
    int MPI_SOURCE;
    int MPI_TAG;
    int MPI_ERROR;
} MPI_Status;

/* Must be able to hold any valid address.  64 bit machines may need
   to change this */
#if (defined(_SX) && !defined(_LONG64))
/* NEC SX-4 in some modes needs this */
typedef long long MPI_Aint;
#else
typedef long MPI_Aint;
#endif

/* MPI Error handlers.  Systems that don't support stdargs can't use
   this definition
 */
#if defined(USE_STDARG) 
typedef void (MPI_Handler_function) MPIR_ARGS(( MPI_Comm *, int *, ... ));
#else
typedef void (MPI_Handler_function) ();
#endif

#define MPI_ERRORS_ARE_FATAL ((MPI_Errhandler)119)
#define MPI_ERRORS_RETURN    ((MPI_Errhandler)120)
#define MPIR_ERRORS_WARN     ((MPI_Errhandler)121)
typedef int MPI_Errhandler;
/* Make the C names for the null functions all upper-case.  Note that 
   this is required for systems that use all uppercase names for Fortran 
   externals.  */
#define MPI_NULL_COPY_FN   MPIR_null_copy_fn
#define MPI_NULL_DELETE_FN MPIR_null_delete_fn
#define MPI_DUP_FN         MPIR_dup_fn

/* MPI request opjects */
typedef union MPIR_HANDLE *MPI_Request;

/* User combination function */
typedef void (MPI_User_function) MPIR_ARGS(( void *, void *, int *, 
					     MPI_Datatype *)); 

/* MPI Attribute copy and delete functions */
typedef int (MPI_Copy_function) MPIR_ARGS(( MPI_Comm, int, void *,
					    void *, void *, int *));
typedef int (MPI_Delete_function) MPIR_ARGS(( MPI_Comm, int, void *, void * ));

#define MPI_VERSION 1
#define MPI_SUBVERSION 2

/********************** MPI-2 FEATURES BEGIN HERE ***************************/
#define MPICH_HAS_HANDLE2INT

/* Handle conversion types/functions */
typedef void *MPI_Handle_type;
/* Note: this may need to be typedef long MPI_Fint; instead */
typedef int  MPI_Fint;
typedef enum { MPI_DATATYPE_HANDLE, MPI_REQUEST_HANDLE, MPI_COMM_HANDLE, 
	       MPI_GROUP_HANDLE, MPI_ERRHANDLE_HANDLE, MPI_OP_HANDLE } 
MPI_Handle_enum;

/* These routines have changed(!) */
MPI_Handle_type MPI_Int2handle MPIR_ARGS(( MPI_Fint, MPI_Handle_enum ));
MPI_Fint MPI_Handle2int MPIR_ARGS(( MPI_Handle_type, MPI_Handle_enum ));

/********************** MPI-2 FEATURES END HERE ***************************/

/* MPI's error classes */
/* error codes for MPI programs
   MAKE SURE YOU UPDATE mpif.h if you change this file! */

#ifndef MPI_SUCCESS

/* Note that there are only a few error CLASSES, and these are all that
   are defined as standard.   Everything else should be an error CODE,
   mapped into an error class.
   An implementation MAY define MPI_ERR_xxxx as error CODES, but
   they must map into one of these classes.
 */
/* error return classes */
#define MPI_SUCCESS          0      /* Successful return code */
#define MPI_ERR_BUFFER       1      /* Invalid buffer pointer */
#define MPI_ERR_COUNT        2      /* Invalid count argument */
#define MPI_ERR_TYPE         3      /* Invalid datatype argument */
#define MPI_ERR_TAG          4      /* Invalid tag argument */
#define MPI_ERR_COMM         5      /* Invalid communicator */
#define MPI_ERR_RANK         6      /* Invalid rank */
#define MPI_ERR_ROOT         7      /* Invalid root */
#define MPI_ERR_GROUP        8      /* Null group passed to function */
#define MPI_ERR_OP           9      /* Invalid operation */
#define MPI_ERR_TOPOLOGY    10      /* Invalid topology */
#define MPI_ERR_DIMS        11      /* Illegal dimension argument */
#define MPI_ERR_ARG         12      /* Invalid argument */
#define MPI_ERR_UNKNOWN     13      /* Unknown error */
#define MPI_ERR_TRUNCATE    14      /* message truncated on receive */
#define MPI_ERR_OTHER       15      /* Other error; use Error_string */
#define MPI_ERR_INTERN      16      /* internal error code    */
#define MPI_ERR_IN_STATUS   17      /* Look in status for error value */
#define MPI_ERR_PENDING     18      /* Pending request */
#define MPI_ERR_REQUEST     19      /* illegal mpi_request handle */
#define MPI_ERR_LASTCODE    (256*16+18)      /* Last error code*/

#endif /* MPI_SUCCESS */

/* Bindings of the MPI routines */
#ifdef __TRAPPER
#define TRAPPER_ANIMATION
#include "trapperb.h"
#endif

#define MPIAPI __declspec(dllimport)

/* #if defined(__STDC__) || defined(__cplusplus) || defined(HAVE_PROTOTYPES) */
MPIAPI int MPI_Send(void*, int, MPI_Datatype, int, int, MPI_Comm);
MPIAPI int MPI_Recv(void*, int, MPI_Datatype, int, int, MPI_Comm, MPI_Status *);
#ifdef TRAPPER_ANIMATION
MPIAPI int _MPI_Send(void*, int, MPI_Datatype, int, int, MPI_Comm, short, short);
MPIAPI int _MPI_Recv(void*, int, MPI_Datatype, int, int, MPI_Comm, MPI_Status *, short, short);
#endif
MPIAPI int MPI_Get_count(MPI_Status *, MPI_Datatype, int *);
MPIAPI int MPI_Bsend(void*, int, MPI_Datatype, int, int, MPI_Comm);
MPIAPI int MPI_Ssend(void*, int, MPI_Datatype, int, int, MPI_Comm);
MPIAPI int MPI_Rsend(void*, int, MPI_Datatype, int, int, MPI_Comm);
#ifdef TRAPPER_ANIMATION
MPIAPI int _MPI_Bsend(void*, int, MPI_Datatype, int, int, MPI_Comm, short, short);
MPIAPI int _MPI_Ssend(void*, int, MPI_Datatype, int, int, MPI_Comm, short, short);
MPIAPI int _MPI_Rsend(void*, int, MPI_Datatype, int, int, MPI_Comm, short, short);
#endif
MPIAPI int MPI_Buffer_attach( void*, int);
MPIAPI int MPI_Buffer_detach( void*, int*);
MPIAPI int MPI_Isend(void*, int, MPI_Datatype, int, int, MPI_Comm, MPI_Request *);
MPIAPI int MPI_Ibsend(void*, int, MPI_Datatype, int, int, MPI_Comm, MPI_Request *);
MPIAPI int MPI_Issend(void*, int, MPI_Datatype, int, int, MPI_Comm, MPI_Request *);
MPIAPI int MPI_Irsend(void*, int, MPI_Datatype, int, int, MPI_Comm, MPI_Request *);
MPIAPI int MPI_Irecv(void*, int, MPI_Datatype, int, int, MPI_Comm, MPI_Request *);
MPIAPI int MPI_Wait(MPI_Request *, MPI_Status *);
#ifdef TRAPPER_ANIMATION
MPIAPI int _MPI_Isend(void*, int, MPI_Datatype, int, int, MPI_Comm, MPI_Request *, short, short);
MPIAPI int _MPI_Ibsend(void*, int, MPI_Datatype, int, int, MPI_Comm, MPI_Request *, short, short);
MPIAPI int _MPI_Issend(void*, int, MPI_Datatype, int, int, MPI_Comm, MPI_Request *, short, short);
MPIAPI int _MPI_Irsend(void*, int, MPI_Datatype, int, int, MPI_Comm, MPI_Request *, short, short);
MPIAPI int _MPI_Irecv(void*, int, MPI_Datatype, int, int, MPI_Comm, MPI_Request *, short, short);
MPIAPI int _MPI_Wait(MPI_Request *, MPI_Status *, short, short);
#endif
MPIAPI int MPI_Test(MPI_Request *, int *, MPI_Status *);
MPIAPI int MPI_Request_free(MPI_Request *);
MPIAPI int MPI_Waitany(int, MPI_Request *, int *, MPI_Status *);
#ifdef TRAPPER_ANIMATION
MPIAPI int _MPI_Waitany(int, MPI_Request *, int *, MPI_Status *, short, short);
#endif
MPIAPI int MPI_Testany(int, MPI_Request *, int *, int *, MPI_Status *);
MPIAPI int MPI_Waitall(int, MPI_Request *, MPI_Status *);
#ifdef TRAPPER_ANIMATION
MPIAPI int _MPI_Waitall(int, MPI_Request *, MPI_Status *, short, short);
#endif
MPIAPI int MPI_Testall(int, MPI_Request *, int *, MPI_Status *);
MPIAPI int MPI_Waitsome(int, MPI_Request *, int *, int *, MPI_Status *);
#ifdef TRAPPER_ANIMATION
MPIAPI int _MPI_Waitsome(int, MPI_Request *, int *, int *, MPI_Status *, short, short);
#endif
MPIAPI int MPI_Testsome(int, MPI_Request *, int *, int *, MPI_Status *);
MPIAPI int MPI_Iprobe(int, int, MPI_Comm, int *flag, MPI_Status *);
MPIAPI int MPI_Probe(int, int, MPI_Comm, MPI_Status *);
#ifdef TRAPPER_ANIMATION
MPIAPI int _MPI_Probe(int, int, MPI_Comm, MPI_Status *, short, short);
#endif
MPIAPI int MPI_Cancel(MPI_Request *);
MPIAPI int MPI_Test_cancelled(MPI_Status *, int *flag);
MPIAPI int MPI_Send_init(void*, int, MPI_Datatype, int, int, MPI_Comm, MPI_Request *);
MPIAPI int MPI_Bsend_init(void*, int, MPI_Datatype, int,int, MPI_Comm, MPI_Request *);
MPIAPI int MPI_Ssend_init(void*, int, MPI_Datatype, int,int, MPI_Comm, MPI_Request *);
MPIAPI int MPI_Rsend_init(void*, int, MPI_Datatype, int,int, MPI_Comm, MPI_Request *);
MPIAPI int MPI_Recv_init(void*, int, MPI_Datatype, int,int, MPI_Comm, MPI_Request *);
MPIAPI int MPI_Start(MPI_Request *);
MPIAPI int MPI_Startall(int, MPI_Request *);
MPIAPI int MPI_Sendrecv(void *, int, MPI_Datatype,int, int, void *, int, 
		 MPI_Datatype, int, int, MPI_Comm, MPI_Status *);
MPIAPI int MPI_Sendrecv_replace(void*, int, MPI_Datatype, 
			 int, int, int, int, MPI_Comm, MPI_Status *);
MPIAPI int MPI_Type_contiguous(int, MPI_Datatype, MPI_Datatype *);
MPIAPI int MPI_Type_vector(int, int, int, MPI_Datatype, MPI_Datatype *);
MPIAPI int MPI_Type_hvector(int, int, MPI_Aint, MPI_Datatype, MPI_Datatype *);
MPIAPI int MPI_Type_indexed(int, int *, int *, MPI_Datatype, MPI_Datatype *);
MPIAPI int MPI_Type_hindexed(int, int *, MPI_Aint *, MPI_Datatype, MPI_Datatype *);
MPIAPI int MPI_Type_struct(int, int *, MPI_Aint *, MPI_Datatype *, MPI_Datatype *);
MPIAPI int MPI_Address(void*, MPI_Aint *);
MPIAPI int MPI_Type_extent(MPI_Datatype, MPI_Aint *);

/* See the 1.1 version of the Standard; I think that the standard is in 
   error; however, it is the standard */
/* int MPI_Type_size(MPI_Datatype, MPI_Aint *size); */
MPIAPI int MPI_Type_size(MPI_Datatype, int *);
MPIAPI int MPI_Type_count(MPI_Datatype, int *);
MPIAPI int MPI_Type_lb(MPI_Datatype, MPI_Aint*);
MPIAPI int MPI_Type_ub(MPI_Datatype, MPI_Aint*);
MPIAPI int MPI_Type_commit(MPI_Datatype *);
MPIAPI int MPI_Type_free(MPI_Datatype *);
MPIAPI int MPI_Get_elements(MPI_Status *, MPI_Datatype, int *);
MPIAPI int MPI_Pack(void* inbuf, int, MPI_Datatype, void *outbuf, 
	     int outsize, int *position,  MPI_Comm);
MPIAPI int MPI_Unpack(void* inbuf, int insize, int *position, void *outbuf, 
	       int , MPI_Datatype, MPI_Comm);
MPIAPI int MPI_Pack_size(int, MPI_Datatype, MPI_Comm, 
		  int *);
MPIAPI int MPI_Barrier(MPI_Comm );

MPIAPI int MPI_Bcast(void*fer, int, MPI_Datatype, int root, 
	      MPI_Comm );
MPIAPI int MPI_Gather(void* , int, MPI_Datatype, 
	       void*, int, MPI_Datatype, 
	       int root, MPI_Comm); 
MPIAPI int MPI_Gatherv(void* , int, MPI_Datatype, 
		void*, int *recvcounts, int *displs, 
		MPI_Datatype, int root, MPI_Comm); 
MPIAPI int MPI_Scatter(void* , int, MPI_Datatype, 
		void*, int, MPI_Datatype, 
		int root, MPI_Comm);
MPIAPI int MPI_Scatterv(void* , int *sendcounts, int *displs, 
		 MPI_Datatype, void*, int, 
		 MPI_Datatype, int root, MPI_Comm);
MPIAPI int MPI_Allgather(void* , int, MPI_Datatype,
		  void*, int, MPI_Datatype, 
		  MPI_Comm);
MPIAPI int MPI_Allgatherv(void* , int, MPI_Datatype, 
		   void*, int *recvcounts, int *displs, 
		   MPI_Datatype, MPI_Comm);
MPIAPI int MPI_Alltoall(void* , int, MPI_Datatype, 
		 void*, int, MPI_Datatype, 
		 MPI_Comm);
MPIAPI int MPI_Alltoallv(void* , int *sendcounts, int *sdispls, 
		  MPI_Datatype, void*, int *recvcounts, 
		  int *rdispls, MPI_Datatype, MPI_Comm);
MPIAPI int MPI_Reduce(void* , void*, int, 
	       MPI_Datatype, MPI_Op op, int root, MPI_Comm);
#ifdef TRAPPER_ANIMATION
MPIAPI int _MPI_Barrier(MPI_Comm, short, short);

MPIAPI int _MPI_Bcast(void*fer, int, MPI_Datatype, int root, 
	      MPI_Comm, short, short );
MPIAPI int _MPI_Gather(void* , int, MPI_Datatype, 
	       void*, int, MPI_Datatype, 
	       int root, MPI_Comm, short, short); 
MPIAPI int _MPI_Gatherv(void* , int, MPI_Datatype, 
		void*, int *recvcounts, int *displs, 
		MPI_Datatype, int root, MPI_Comm, short, short); 
MPIAPI int _MPI_Scatter(void* , int, MPI_Datatype, 
		void*, int, MPI_Datatype, 
		int root, MPI_Comm, short, short);
MPIAPI int _MPI_Scatterv(void* , int *sendcounts, int *displs, 
		 MPI_Datatype, void*, int, 
		 MPI_Datatype, int root, MPI_Comm, short, short);
MPIAPI int _MPI_Allgather(void* , int, MPI_Datatype, 
		  void*, int, MPI_Datatype, 
		  MPI_Comm, short, short);
MPIAPI int _MPI_Allgatherv(void* , int, MPI_Datatype, 
		   void*, int *recvcounts, int *displs,
		   MPI_Datatype, MPI_Comm, short, short);
MPIAPI int _MPI_Alltoall(void* , int, MPI_Datatype, 
		 void*, int, MPI_Datatype, 
		 MPI_Comm, short, short);
MPIAPI int _MPI_Alltoallv(void* , int *sendcounts, int *sdispls, 
		  MPI_Datatype, void*, int *recvcounts, 
		  int *rdispls, MPI_Datatype, MPI_Comm, short, short);
MPIAPI int _MPI_Reduce(void* , void*, int, 
	       MPI_Datatype, MPI_Op op, int root, MPI_Comm, short, short);
#endif
MPIAPI int MPI_Op_create(MPI_User_function *, int, MPI_Op *);
MPIAPI int MPI_Op_free( MPI_Op *);
MPIAPI int MPI_Allreduce(void* , void*, int, 
		  MPI_Datatype, MPI_Op op, MPI_Comm);
MPIAPI int MPI_Reduce_scatter(void* , void*, int *recvcounts, 
		       MPI_Datatype, MPI_Op op, MPI_Comm);
MPIAPI int MPI_Scan(void* , void*, int, MPI_Datatype, 
	     MPI_Op op, MPI_Comm );
#ifdef TRAPPER_ANIMATION
MPIAPI int _MPI_Allreduce(void* , void*, int, 
		  MPI_Datatype, MPI_Op op, MPI_Comm, short, short);
MPIAPI int _MPI_Reduce_scatter(void* , void*, int *recvcounts, 
		       MPI_Datatype, MPI_Op op, MPI_Comm, short, short);
MPIAPI int _MPI_Scan(void* , void*, int, MPI_Datatype, 
	     MPI_Op op, MPI_Comm, short, short );
#endif
MPIAPI int MPI_Group_size(MPI_Group group, int *);
MPIAPI int MPI_Group_rank(MPI_Group group, int *rank);
MPIAPI int MPI_Group_translate_ranks (MPI_Group group1, int n, int *ranks1, 
			       MPI_Group group2, int *ranks2);
MPIAPI int MPI_Group_compare(MPI_Group group1, MPI_Group group2, int *result);
MPIAPI int MPI_Comm_group(MPI_Comm, MPI_Group *);
MPIAPI int MPI_Group_union(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup);
MPIAPI int MPI_Group_intersection(MPI_Group group1, MPI_Group group2, 
			   MPI_Group *newgroup);
MPIAPI int MPI_Group_difference(MPI_Group group1, MPI_Group group2, 
			 MPI_Group *newgroup);
MPIAPI int MPI_Group_incl(MPI_Group group, int n, int *ranks, MPI_Group *newgroup);
MPIAPI int MPI_Group_excl(MPI_Group group, int n, int *ranks, MPI_Group *newgroup);
MPIAPI int MPI_Group_range_incl(MPI_Group group, int n, int ranges[][3], 
			 MPI_Group *newgroup);
MPIAPI int MPI_Group_range_excl(MPI_Group group, int n, int ranges[][3], 
			 MPI_Group *newgroup);
MPIAPI int MPI_Group_free(MPI_Group *);
MPIAPI int MPI_Comm_size(MPI_Comm, int *);
MPIAPI int MPI_Comm_rank(MPI_Comm, int *rank);
MPIAPI int MPI_Comm_compare(MPI_Comm, MPI_Comm, int *result);
MPIAPI int MPI_Comm_dup(MPI_Comm, MPI_Comm *newcomm);
MPIAPI int MPI_Comm_create(MPI_Comm, MPI_Group group, MPI_Comm *newcomm);
MPIAPI int MPI_Comm_split(MPI_Comm, int color, int key, MPI_Comm *newcomm);
MPIAPI int MPI_Comm_free(MPI_Comm *comm);
MPIAPI int MPI_Comm_test_inter(MPI_Comm, int *flag);
MPIAPI int MPI_Comm_remote_size(MPI_Comm, int *);
MPIAPI int MPI_Comm_remote_group(MPI_Comm, MPI_Group *);
MPIAPI int MPI_Intercomm_create(MPI_Comm local_comm, int local_leader, 
			 MPI_Comm peer_comm, int remote_leader, 
			 int, MPI_Comm *newintercomm);
MPIAPI int MPI_Intercomm_merge(MPI_Comm intercomm, int high, MPI_Comm *newintracomm);
MPIAPI int MPI_Keyval_create(MPI_Copy_function *copy_fn, 
		      MPI_Delete_function *delete_fn, 
		      int *keyval, void* extra_state);
MPIAPI int MPI_Keyval_free(int *keyval);
MPIAPI int MPI_Attr_put(MPI_Comm, int keyval, void* attribute_val);
MPIAPI int MPI_Attr_get(MPI_Comm, int keyval, void *attribute_val, int *flag);
MPIAPI int MPI_Attr_delete(MPI_Comm, int keyval);
MPIAPI int MPI_Topo_test(MPI_Comm, int *);
MPIAPI int MPI_Cart_create(MPI_Comm comm_old, int ndims, int *dims, int *periods,
		    int reorder, MPI_Comm *comm_cart);
MPIAPI int MPI_Dims_create(int nnodes, int ndims, int *dims);
MPIAPI int MPI_Graph_create(MPI_Comm, int, int *, int *, int, MPI_Comm *);
MPIAPI int MPI_Graphdims_get(MPI_Comm, int *nnodes, int *nedges);
MPIAPI int MPI_Graph_get(MPI_Comm, int, int, int *, int *);
MPIAPI int MPI_Cartdim_get(MPI_Comm, int *ndims);
MPIAPI int MPI_Cart_get(MPI_Comm, int maxdims, int *dims, int *periods,
		 int *coords);
MPIAPI int MPI_Cart_rank(MPI_Comm, int *coords, int *rank);
MPIAPI int MPI_Cart_coords(MPI_Comm, int rank, int maxdims, int *coords);
MPIAPI int MPI_Graph_neighbors_count(MPI_Comm, int rank, int *nneighbors);
MPIAPI int MPI_Graph_neighbors(MPI_Comm, int rank, int maxneighbors,
			int *neighbors);
MPIAPI int MPI_Cart_shift(MPI_Comm, int direction, int disp, 
		   int *rank_source, int *rank_dest);
MPIAPI int MPI_Cart_sub(MPI_Comm, int *remain_dims, MPI_Comm *newcomm);
MPIAPI int MPI_Cart_map(MPI_Comm, int ndims, int *dims, int *periods, 
		 int *newrank);
MPIAPI int MPI_Graph_map(MPI_Comm, int, int *, int *, int *);
MPIAPI int MPI_Get_processor_name(char *, int *);
MPIAPI int MPI_Errhandler_create(MPI_Handler_function *function, 
			  MPI_Errhandler *errhandler);
MPIAPI int MPI_Errhandler_set(MPI_Comm, MPI_Errhandler errhandler);
MPIAPI int MPI_Errhandler_get(MPI_Comm, MPI_Errhandler *errhandler);
MPIAPI int MPI_Errhandler_free(MPI_Errhandler *errhandler);
MPIAPI int MPI_Error_string(int errorcode, char *string, int *result_len);
MPIAPI int MPI_Error_class(int errorcode, int *errorclass);
MPIAPI double MPI_Wtime(void);
MPIAPI double MPI_Wtick(void);
#ifndef MPI_Wtime
MPIAPI double PMPI_Wtime(void);
MPIAPI double PMPI_Wtick(void);
#endif
MPIAPI int MPI_Init(int *argc, char ***argv);
MPIAPI int MPI_Finalize(void);
MPIAPI int MPI_Initialized(int *flag);
MPIAPI int MPI_Abort(MPI_Comm, int errorcode);

#ifdef TRAPPER_ANIMATION
MPIAPI int _MPI_Init(int *argc, char ***argv, short file, short line);
MPIAPI int _MPI_Finalize(short file, short line);
MPIAPI int _MPI_Abort(MPI_Comm, int errorcode, short file, short line);
#endif
/* MPI-2 communicator naming functions */
MPIAPI int MPI_Comm_set_name(MPI_Comm, char *);
MPIAPI int MPI_Comm_get_name(MPI_Comm, char **);
#ifdef HAVE_NO_C_CONST
/* Default Solaris compiler does not accept const but does accept prototypes */
MPIAPI int MPI_Pcontrol(int level, ...);
#else
MPIAPI int MPI_Pcontrol(const int level, ...);
#endif

MPIAPI int MPI_NULL_COPY_FN ( MPI_Comm oldcomm, int keyval, void *extra_state, 
		       void *attr_in, void *attr_out, int *flag );
MPIAPI int MPI_NULL_DELETE_FN ( MPI_Comm, int keyval, void *attr, 
			 void *extra_state );
MPIAPI int MPI_DUP_FN ( MPI_Comm, int keyval, void *extra_state, void *attr_in,
		 void *attr_out, int *flag );

/* MPI-1.2 Function */
MPIAPI int MPI_Get_version(int *, int *);

/* Here are the bindings of the profiling routines */
#if !defined(MPI_BUILD_PROFILING)
MPIAPI int PMPI_Send(void*, int, MPI_Datatype, int, int, 
	     MPI_Comm);
MPIAPI int PMPI_Recv(void*, int, MPI_Datatype, int, 
	     int, MPI_Comm, MPI_Status *);
MPIAPI int PMPI_Get_count(MPI_Status *, MPI_Datatype, int *);
MPIAPI int PMPI_Bsend(void*, int, MPI_Datatype, int, int, 
	      MPI_Comm);
MPIAPI int PMPI_Ssend(void*, int, MPI_Datatype, int, int, 
	      MPI_Comm);
MPIAPI int PMPI_Rsend(void*, int, MPI_Datatype, int, int, 
	      MPI_Comm);
MPIAPI int PMPI_Buffer_attach( void* buffer, int size);
MPIAPI int PMPI_Buffer_detach( void* buffer, int* size);
MPIAPI int PMPI_Isend(void*, int, MPI_Datatype, int, int, 
	      MPI_Comm, MPI_Request *);
MPIAPI int PMPI_Ibsend(void*, int, MPI_Datatype, int, 
	       int, MPI_Comm, MPI_Request *);
MPIAPI int PMPI_Issend(void*, int, MPI_Datatype, int, 
	       int, MPI_Comm, MPI_Request *);
MPIAPI int PMPI_Irsend(void*, int, MPI_Datatype, int, 
	       int, MPI_Comm, MPI_Request *);
MPIAPI int PMPI_Irecv(void*, int, MPI_Datatype, int, 
	      int, MPI_Comm, MPI_Request *);
MPIAPI int PMPI_Wait(MPI_Request *, MPI_Status *);
MPIAPI int PMPI_Test(MPI_Request *, int *flag, MPI_Status *);
MPIAPI int PMPI_Request_free(MPI_Request *);
MPIAPI int PMPI_Waitany(int, MPI_Request *, int *, MPI_Status *);
MPIAPI int PMPI_Testany(int, MPI_Request *, int *, int *, MPI_Status *);
MPIAPI int PMPI_Waitall(int, MPI_Request *, 
		MPI_Status *);
MPIAPI int PMPI_Testall(int, MPI_Request *, int *flag,
		MPI_Status *);
MPIAPI int PMPI_Waitsome(int, MPI_Request *, int *,
		 int *, MPI_Status *);
MPIAPI int PMPI_Testsome(int, MPI_Request *, int *, 
		 int *, MPI_Status *);
MPIAPI int PMPI_Iprobe(int, int, MPI_Comm, int *flag, 
	       MPI_Status *);
MPIAPI int PMPI_Probe(int, int, MPI_Comm, MPI_Status *);
MPIAPI int PMPI_Cancel(MPI_Request *);
MPIAPI int PMPI_Test_cancelled(MPI_Status *, int *flag);
MPIAPI int PMPI_Send_init(void*, int, MPI_Datatype, int, 
		  int, MPI_Comm, MPI_Request *);
MPIAPI int PMPI_Bsend_init(void*, int, MPI_Datatype, int, 
		   int, MPI_Comm, MPI_Request *);
MPIAPI int PMPI_Ssend_init(void*, int, MPI_Datatype, int, 
		   int, MPI_Comm, MPI_Request *);
MPIAPI int PMPI_Rsend_init(void*, int, MPI_Datatype, int, 
		   int, MPI_Comm, MPI_Request *);
MPIAPI int PMPI_Recv_init(void*, int, MPI_Datatype, int, 
		  int, MPI_Comm, MPI_Request *);
MPIAPI int PMPI_Start(MPI_Request *);
MPIAPI int PMPI_Startall(int, MPI_Request *);
MPIAPI int PMPI_Sendrecv(void *, int, MPI_Datatype, 
		 int, int, void *, int, 
		 MPI_Datatype, int, int, 
		 MPI_Comm, MPI_Status *);
MPIAPI int PMPI_Sendrecv_replace(void*, int, MPI_Datatype, 
			 int, int, int, int, 
			 MPI_Comm, MPI_Status *);
MPIAPI int PMPI_Type_contiguous(int, MPI_Datatype, 
			MPI_Datatype *);
MPIAPI int PMPI_Type_vector(int, int, int, 
		    MPI_Datatype, MPI_Datatype *);
MPIAPI int PMPI_Type_hvector(int, int, MPI_Aint, 
		     MPI_Datatype, MPI_Datatype *);
MPIAPI int PMPI_Type_indexed(int, int *, 
		     int *, MPI_Datatype, 
		     MPI_Datatype *);
MPIAPI int PMPI_Type_hindexed(int, int *, 
		      MPI_Aint *, MPI_Datatype, 
		      MPI_Datatype *);
MPIAPI int PMPI_Type_struct(int, int *, 
		    MPI_Aint *, 
		    MPI_Datatype *, MPI_Datatype *);
MPIAPI int PMPI_Address(void*, MPI_Aint *);
MPIAPI int PMPI_Type_extent(MPI_Datatype, MPI_Aint *);

/* See the 1.1 version of the Standard; I think that the standard is in 
   error; however, it is the standard */
/* MPIAPI int PMPI_Type_size(MPI_Datatype, MPI_Aint *); */
MPIAPI int PMPI_Type_size(MPI_Datatype, int *);
MPIAPI int PMPI_Type_count(MPI_Datatype, int *);
MPIAPI int PMPI_Type_lb(MPI_Datatype, MPI_Aint*);
MPIAPI int PMPI_Type_ub(MPI_Datatype, MPI_Aint*);
MPIAPI int PMPI_Type_commit(MPI_Datatype *);
MPIAPI int PMPI_Type_free(MPI_Datatype *);
MPIAPI int PMPI_Get_elements(MPI_Status *, MPI_Datatype, int *);
MPIAPI int PMPI_Pack(void* inbuf, int, MPI_Datatype, void *outbuf, 
	     int outsize, int *position,  MPI_Comm);
MPIAPI int PMPI_Unpack(void*, int, int *, void *, 
	       int, MPI_Datatype, MPI_Comm);
MPIAPI int PMPI_Pack_size(int, MPI_Datatype, MPI_Comm, 
		  int *);
MPIAPI int PMPI_Barrier(MPI_Comm );
MPIAPI int PMPI_Bcast(void* buffer, int, MPI_Datatype, int root, 
	      MPI_Comm );
MPIAPI int PMPI_Gather(void* , int, MPI_Datatype, 
	       void*, int, MPI_Datatype,
	       int root, MPI_Comm); 
MPIAPI int PMPI_Gatherv(void* , int, MPI_Datatype, 
		void*, int *recvcounts, int *displs, 
		MPI_Datatype, int root, MPI_Comm); 
MPIAPI int PMPI_Scatter(void* , int, MPI_Datatype, 
		void*, int, MPI_Datatype, 
		int root, MPI_Comm);
MPIAPI int PMPI_Scatterv(void* , int *sendcounts, int *displs, 
		 MPI_Datatype, void*, int, 
		 MPI_Datatype, int root, MPI_Comm);
MPIAPI int PMPI_Allgather(void* , int, MPI_Datatype, 
		  void*, int, MPI_Datatype, 
		  MPI_Comm);
MPIAPI int PMPI_Allgatherv(void* , int, MPI_Datatype, 
		   void*, int *recvcounts, int *displs, 
		   MPI_Datatype, MPI_Comm);
MPIAPI int PMPI_Alltoall(void* , int, MPI_Datatype, 
		 void*, int, MPI_Datatype, 
		 MPI_Comm);
MPIAPI int PMPI_Alltoallv(void* , int *sendcounts, int *sdispls, 
		  MPI_Datatype, void*, int *recvcounts, 
		  int *rdispls, MPI_Datatype, MPI_Comm);
MPIAPI int PMPI_Reduce(void* , void*, int, 
	       MPI_Datatype, MPI_Op op, int root, MPI_Comm);
MPIAPI int PMPI_Op_create(MPI_User_function *, int, MPI_Op *);
MPIAPI int PMPI_Op_free( MPI_Op *);
MPIAPI int PMPI_Allreduce(void* , void*, int, 
		  MPI_Datatype, MPI_Op op, MPI_Comm);
MPIAPI int PMPI_Reduce_scatter(void* , void*, int *recvcounts, 
		       MPI_Datatype, MPI_Op op, MPI_Comm);
MPIAPI int PMPI_Scan(void* , void*, int, MPI_Datatype,
	     MPI_Op op, MPI_Comm );
MPIAPI int PMPI_Group_size(MPI_Group group, int *);
MPIAPI int PMPI_Group_rank(MPI_Group group, int *rank);
MPIAPI int PMPI_Group_translate_ranks (MPI_Group group1, int n, int *ranks1, 
			       MPI_Group group2, int *ranks2);
MPIAPI int PMPI_Group_compare(MPI_Group group1, MPI_Group group2, int *result);
MPIAPI int PMPI_Comm_group(MPI_Comm, MPI_Group *);
MPIAPI int PMPI_Group_union(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup);
MPIAPI int PMPI_Group_intersection(MPI_Group group1, MPI_Group group2, 
			   MPI_Group *newgroup);
MPIAPI int PMPI_Group_difference(MPI_Group group1, MPI_Group group2, 
			 MPI_Group *newgroup);
MPIAPI int PMPI_Group_incl(MPI_Group group, int n, int *ranks, MPI_Group *newgroup);
MPIAPI int PMPI_Group_excl(MPI_Group group, int n, int *ranks, MPI_Group *newgroup);
MPIAPI int PMPI_Group_range_incl(MPI_Group group, int n, int ranges[][3], 
			 MPI_Group *newgroup);
MPIAPI int PMPI_Group_range_excl(MPI_Group group, int n, int ranges[][3], 
			 MPI_Group *newgroup);
MPIAPI int PMPI_Group_free(MPI_Group *);
MPIAPI int PMPI_Comm_size(MPI_Comm, int *);
MPIAPI int PMPI_Comm_rank(MPI_Comm, int *rank);
MPIAPI int PMPI_Comm_compare(MPI_Comm comm1, MPI_Comm comm2, int *result);
MPIAPI int PMPI_Comm_dup(MPI_Comm, MPI_Comm *newcomm);
MPIAPI int PMPI_Comm_create(MPI_Comm, MPI_Group group, MPI_Comm *newcomm);
MPIAPI int PMPI_Comm_split(MPI_Comm, int color, int key, MPI_Comm *newcomm);
MPIAPI int PMPI_Comm_free(MPI_Comm *comm);
MPIAPI int PMPI_Comm_test_inter(MPI_Comm, int *flag);
MPIAPI int PMPI_Comm_remote_size(MPI_Comm, int *);
MPIAPI int PMPI_Comm_remote_group(MPI_Comm, MPI_Group *);
MPIAPI int PMPI_Intercomm_create(MPI_Comm local_comm, int local_leader, 
			 MPI_Comm peer_comm, int remote_leader, 
			 int, MPI_Comm *newintercomm);
MPIAPI int PMPI_Intercomm_merge(MPI_Comm intercomm, int high, MPI_Comm *newintracomm);
MPIAPI int PMPI_Keyval_create(MPI_Copy_function *copy_fn, 
		      MPI_Delete_function *delete_fn,
		      int *keyval, void* extra_state);
MPIAPI int PMPI_Keyval_free(int *keyval);
MPIAPI int PMPI_Attr_put(MPI_Comm, int keyval, void* attribute_val);
MPIAPI int PMPI_Attr_get(MPI_Comm, int keyval, void *attribute_val, int *flag);
MPIAPI int PMPI_Attr_delete(MPI_Comm, int keyval);
MPIAPI int PMPI_Topo_test(MPI_Comm, int *);
MPIAPI int PMPI_Cart_create(MPI_Comm comm_old, int ndims, int *dims, int *periods,
		    int reorder, MPI_Comm *comm_cart);
MPIAPI int PMPI_Dims_create(int nnodes, int ndims, int *dims);
MPIAPI int PMPI_Graph_create(MPI_Comm, int, int *, int *, int, MPI_Comm *);
MPIAPI int PMPI_Graphdims_get(MPI_Comm, int *nnodes, int *nedges);
MPIAPI int PMPI_Graph_get(MPI_Comm, int, int, int *, int *);
MPIAPI int PMPI_Cartdim_get(MPI_Comm, int *ndims);
MPIAPI int PMPI_Cart_get(MPI_Comm, int maxdims, int *dims, int *periods,
		 int *coords);
MPIAPI int PMPI_Cart_rank(MPI_Comm, int *coords, int *rank);
MPIAPI int PMPI_Cart_coords(MPI_Comm, int rank, int maxdims, int *coords);
MPIAPI int PMPI_Graph_neighbors_count(MPI_Comm, int rank, int *nneighbors);
MPIAPI int PMPI_Graph_neighbors(MPI_Comm, int rank, int maxneighbors,
			int *neighbors);
MPIAPI int PMPI_Cart_shift(MPI_Comm, int direction, int disp, 
		   int *rank_source, int *rank_dest);
MPIAPI int PMPI_Cart_sub(MPI_Comm, int *remain_dims, MPI_Comm *newcomm);
MPIAPI int PMPI_Cart_map(MPI_Comm, int ndims, int *dims, int *periods, 
		 int *newrank);
MPIAPI int PMPI_Graph_map(MPI_Comm, int, int *, int *, int *);
MPIAPI int PMPI_Get_processor_name(char *, int *);
MPIAPI int PMPI_Errhandler_create(MPI_Handler_function *function, 
			  MPI_Errhandler *errhandler);
MPIAPI int PMPI_Errhandler_set(MPI_Comm, MPI_Errhandler errhandler);
MPIAPI int PMPI_Errhandler_get(MPI_Comm, MPI_Errhandler *errhandler);
MPIAPI int PMPI_Errhandler_free(MPI_Errhandler *errhandler);
MPIAPI int PMPI_Error_string(int errorcode, char *string, int *result_len);
MPIAPI int PMPI_Error_class(int errorcode, int *errorclass);
/* Wtime done above */
MPIAPI int PMPI_Init(int *argc, char ***argv);
MPIAPI int PMPI_Finalize(void);
MPIAPI int PMPI_Initialized(int *flag);
MPIAPI int PMPI_Abort(MPI_Comm, int);
/* MPI-2 communicator naming functions */
MPIAPI int PMPI_Comm_set_name(MPI_Comm, char *);
MPIAPI int PMPI_Comm_get_name(MPI_Comm, char **);
#ifdef HAVE_NO_C_CONST
/* Default Solaris compiler does not accept const but does accept prototypes */
MPIAPI int PMPI_Pcontrol(int level, ...);
#else
MPIAPI int PMPI_Pcontrol(const int level, ...);
#endif

/* MPI-1.2 Function - Profiling */
MPIAPI int PMPI_Get_version(int *, int *);

#endif  /* MPI_BUILD_PROFILING */

#else 
extern MPIAPI double MPI_Wtime();
extern MPIAPI double MPI_Wtick();
#ifndef MPI_Wtime
extern MPIAPI double PMPI_Wtime();
extern MPIAPI double PMPI_Wtick();
#endif

extern MPIAPI int MPI_NULL_COPY_FN(), MPI_NULL_DELETE_FN();
/* #endif */

#if defined(__cplusplus)
}
#endif


#ifdef _WINDOWS
#include <STDARG.H>
extern int wp4_putchar(int);
extern int wp4_fputchar(int);
extern int wp4_vprintf (const char *fmt, va_list ap);
extern int wp4_printf (const char *fmt, ...);
extern int wp4_scanf (const char *format, ...);

#ifdef printf
#undef printf
#endif

#ifdef scanf
#undef scanf
#endif

#ifdef putchar
#undef putchar
#endif

#ifdef vprintf
#undef vprintf
#endif

#ifdef fputchar
#undef fputchar
#endif

#define printf wp4_printf
#define scanf wp4_scanf
#define putchar wp4_putchar
#define vprintf wp4_vprintf
#define fputchar wp4_fputchar
#endif

#ifdef _WINDOWS
#ifndef WMPI_WINDOWS
#define WMPI_WINDOWS

#include <windows.h>

HANDLE get_hInstance();

int get_nCmdShow();

#endif
#endif

#endif

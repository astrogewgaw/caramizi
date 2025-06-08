from numpy.typing import ArrayLike
from typing import Annotated, overload


@overload
def dd(
    arg0: Annotated[ArrayLike, dict(dtype="float32", shape=(None, None))],
    arg1: float,
    arg2: float,
    arg3: float,
    arg4: float,
    /,
) -> Annotated[ArrayLike, dict(dtype="float32", shape=(None))]: ...


@overload
def dd(
    arg0: Annotated[ArrayLike, dict(dtype="float64", shape=(None, None))],
    arg1: float,
    arg2: float,
    arg3: float,
    arg4: float,
    /,
) -> Annotated[ArrayLike, dict(dtype="float64", shape=(None))]: ...


@overload
def ddmt(
    arg0: Annotated[ArrayLike, dict(dtype="float32", shape=(None, None))],
    arg1: float,
    arg2: float,
    arg3: float,
    arg4: float,
    arg5: float,
    arg6: int,
    /,
) -> Annotated[ArrayLike, dict(dtype="float32", shape=(None, None))]: ...


@overload
def ddmt(
    arg0: Annotated[ArrayLike, dict(dtype="float64", shape=(None, None))],
    arg1: float,
    arg2: float,
    arg3: float,
    arg4: float,
    arg5: float,
    arg6: int,
    /,
) -> Annotated[ArrayLike, dict(dtype="float64", shape=(None, None))]: ...


@overload
def fold(
    arg0: Annotated[ArrayLike, dict(dtype="float32", shape=(None))],
    arg1: float,
    arg2: float,
    arg3: int,
    arg4: float,
    arg5: float,
    arg6: float,
    arg7: float,
    arg8: bool,
    /,
) -> Annotated[ArrayLike, dict(dtype="float32", shape=(None))]: ...


@overload
def fold(
    arg0: Annotated[ArrayLike, dict(dtype="float64", shape=(None))],
    arg1: float,
    arg2: float,
    arg3: int,
    arg4: float,
    arg5: float,
    arg6: float,
    arg7: float,
    arg8: bool,
    /,
) -> Annotated[ArrayLike, dict(dtype="float64", shape=(None))]: ...


@overload
def inorm(
    arg: Annotated[ArrayLike, dict(dtype="float32", shape=(None))], /
) -> None: ...


@overload
def inorm(
    arg: Annotated[ArrayLike, dict(dtype="float64", shape=(None))], /
) -> None: ...


@overload
def inorm(
    arg: Annotated[ArrayLike, dict(dtype="float32", shape=(None, None))], /
) -> None: ...


@overload
def inorm(
    arg: Annotated[ArrayLike, dict(dtype="float64", shape=(None, None))], /
) -> None: ...


kdm: float = 4149.377593360996


@overload
def norm(
    arg: Annotated[ArrayLike, dict(dtype="float32", shape=(None))], /
) -> Annotated[ArrayLike, dict(dtype="float32", shape=(None))]: ...


@overload
def norm(
    arg: Annotated[ArrayLike, dict(dtype="float64", shape=(None))], /
) -> Annotated[ArrayLike, dict(dtype="float64", shape=(None))]: ...


@overload
def norm(
    arg: Annotated[ArrayLike, dict(dtype="float32", shape=(None, None))], /
) -> Annotated[ArrayLike, dict(dtype="float32", shape=(None, None))]: ...


@overload
def norm(
    arg: Annotated[ArrayLike, dict(dtype="float64", shape=(None, None))], /
) -> Annotated[ArrayLike, dict(dtype="float64", shape=(None, None))]: ...


@overload
def rdd(
    arg0: Annotated[ArrayLike, dict(dtype="float32", shape=(None, None))],
    arg1: float,
    arg2: float,
    arg3: float,
    arg4: float,
    /,
) -> Annotated[ArrayLike, dict(dtype="float32", shape=(None, None))]: ...


@overload
def rdd(
    arg0: Annotated[ArrayLike, dict(dtype="float64", shape=(None, None))],
    arg1: float,
    arg2: float,
    arg3: float,
    arg4: float,
    /,
) -> Annotated[ArrayLike, dict(dtype="float64", shape=(None, None))]: ...


@overload
def runmed(
    arg0: Annotated[ArrayLike, dict(dtype="float32", shape=(None))], arg1: int, /
) -> Annotated[ArrayLike, dict(dtype="float32", shape=(None))]: ...


@overload
def runmed(
    arg0: Annotated[ArrayLike, dict(dtype="float64", shape=(None))], arg1: int, /
) -> Annotated[ArrayLike, dict(dtype="float64", shape=(None))]: ...


@overload
def scrunch(
    arg0: Annotated[ArrayLike, dict(dtype="float32", shape=(None))], arg1: float, /
) -> Annotated[ArrayLike, dict(dtype="float32", shape=(None))]: ...


@overload
def scrunch(
    arg0: Annotated[ArrayLike, dict(dtype="float64", shape=(None))], arg1: float, /
) -> Annotated[ArrayLike, dict(dtype="float64", shape=(None))]: ...

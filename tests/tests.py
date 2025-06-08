import numpy as np
from caramizi import dd, rdd


def test_dd(datadir):
    assert np.allclose(
        np.load(datadir / "ts.npy"),
        dd(
            np.load(datadir / "frb.npy"),
            498.4375,
            200.0,
            1.31072e-3,
            1000.0,
        ),
    )


def test_rdd(datadir):
    assert np.allclose(
        np.load(datadir / "frbdd.npy"),
        np.asarray(
            rdd(
                np.load(datadir / "frb.npy"),
                498.4375,
                200.0,
                1.31072e-3,
                1000.0,
            )
        ).astype(np.uint8),
    )
